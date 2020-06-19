#include"Endecrypter.h"

#include<iostream>
#include<string>
using namespace std;
using std::cout;
using std::cin;
using std::string;

#include<fstream>
using std::ifstream;
using std::ofstream;

#include<string>
using std::string;

#include<thread>
using std::thread;

#include<scrypt.h>
using namespace CryptoPP;
using CryptoPP::Scrypt;

#include <filters.h>
using CryptoPP::StreamTransformationFilter;
using CryptoPP::BlockPaddingSchemeDef;

#include<files.h>
using CryptoPP::FileSink;
using CryptoPP::FileSource;

#include<cryptlib.h>
using CryptoPP::Exception;

#include "aes.h"
using CryptoPP::AES;

#include "ccm.h"
using CryptoPP::CBC_Mode;

void showProgress(ostream* ofs, long size, const char* filePath) {
	long currentSize = 0;
	while (true) {
		this_thread::sleep_for(chrono::seconds(1));

		ifstream is_expired(filePath, ios::in, ios::binary);
		if (is_expired) {
			//expired
			cout << "\33[2K\r100%";
			is_expired.close();
			return;
		}
		else {
			currentSize = ofs->tellp();
		}

		cout.precision(4);
		cout << "\33[2K\r" << (currentSize / (double)size) * 100 << "%";
	}
}

Report Endecrypter::encrypt(const char* targetFilePath, const char* destinationPath, const char* password1, const char* password2) {
	//AES::DEFAULT_KEYLENGTH = 16
	//AES::BLOCKSIZE = 16
	byte key[AES::DEFAULT_KEYLENGTH];
	byte iv[AES::BLOCKSIZE];

	//��й�ȣ�� Key�� IV�� ����� ���� Scrypt ��ü�Դϴ�.
	Scrypt s;
	s.DeriveKey(key, AES::DEFAULT_KEYLENGTH, (byte*)password1, sizeof(password1), g_nullNameValuePairs);
	s.DeriveKey(iv, AES::BLOCKSIZE, (byte*)password2, sizeof(password2), g_nullNameValuePairs);

	try { 
		CBC_Mode<AES>::Encryption e;
		e.SetKeyWithIV(key, sizeof(key), iv);

		//���� ũ�� ���
		ifstream ifs(targetFilePath, ios::binary | ios::in);
		if (!ifs) {
			throw "Cannot read the file";
		}
		ifs.seekg(0, std::ios::end);
		long fileSize = ifs.tellg();
		ifs.close();

		FileSink* fileSink = new FileSink(destinationPath, true);
		StreamTransformationFilter* stf = new StreamTransformationFilter(e, fileSink, BlockPaddingSchemeDef::ZEROS_PADDING);

		//�����带 ���� ��ȣȭ ��ô���� ����ڿ��� �˸��ϴ�.
		ostream* ofs = fileSink->GetStream();
		thread encryptProgress(showProgress, ofs, fileSize, destinationPath);

		FileSource(targetFilePath, true, stf, true);

		encryptProgress.join();
		encryptProgress.~thread();
	}
	catch (const CryptoPP::Exception& e)
	{
		Report rpt(false, e.what());
		return rpt;
	}
	catch (const char* s) {
		Report rpt(false, s);
		return rpt;
	}

	//��� ���Ͽ� �ڱ� �ڽ��� ��ȣȭ�� ���̶�� ǥ���� �ִ´�.(������ �� ��ϸ�(ios::app))
	ofstream appendSignature(destinationPath, ios::app | ios::binary);
	char signature[16] = "DECRYPTED_BY_FL";
	appendSignature.write(signature, 16);	//������ �� ���ڸ� �����Ͽ� �� 16����Ʈ ��ŭ ���ϴ�.

	Report rpt(true);
	return rpt;
}

Report Endecrypter::decrypt(const char* targetFilePath, const char* destinationPath, const char* password1, const char* password2) {
	//�ñ״��ĸ� �˻��Ͽ� �� ���α׷����� ��ȣȭ ���� ���� ������ ��� �����մϴ�.
	char signature[16] = "DECRYPTED_BY_FL";
	char tail[16];
	ifstream verify(targetFilePath, ios::in | ios::binary);

	verify.seekg(-16, ios::end);
	verify.read(tail, 16);
	for (int i = 0; i < 16; i++) {
		if (signature[i] == tail[i]) continue;
		else {
			Report rpt(false, "NOT ENCRYPED BY FILELOCKER.EXE");
			return rpt;
		}
	}	

	//AES::DEFAULT_KEYLENGTH = 16
	//AES::BLOCKSIZE = 16
	byte key[AES::DEFAULT_KEYLENGTH];
	byte iv[AES::BLOCKSIZE];

	//��й�ȣ�� Key�� IV�� ����� ���� Scrypt ��ü�Դϴ�.
	Scrypt s;
	s.DeriveKey(key, AES::DEFAULT_KEYLENGTH, (byte*)password1, sizeof(password1), g_nullNameValuePairs);
	s.DeriveKey(iv, AES::BLOCKSIZE, (byte*)password2, sizeof(password2), g_nullNameValuePairs);

	try {
		CBC_Mode<AES>::Decryption d;
		d.SetKeyWithIV(key, sizeof(key), iv);

		//���� ũ�� ���
		ifstream ifs(targetFilePath, ios::binary | ios::in);
		if (!ifs) {
			throw "Cannot read the file";
		}
		ifs.seekg(0, std::ios::end);
		int fileSize = ifs.tellg();
		ifs.close();

		FileSink* fileSink = new FileSink(destinationPath, true);
		StreamTransformationFilter* stf = new StreamTransformationFilter(d, fileSink, BlockPaddingSchemeDef::ZEROS_PADDING);

		//�����带 ���� ��ȣȭ ��ô���� ����ڿ��� �˸��ϴ�.
		ostream* ofs = fileSink->GetStream();
		thread decryptProgress(&showProgress, ofs, fileSize, destinationPath);

		//FileSource(targetFilePath, true, stf, true);
		ifstream fileSource(targetFilePath, ios::in | ios::binary);
		byte buffer[1024];	//64blocks
		int readBytes;
		while (true) {
			fileSource.read((char*)buffer, 1024);
			readBytes = fileSource.gcount();

			try {
				if (readBytes == 1024) {
					stf->Put(buffer, readBytes);
				}
				else {
					//������ ����� �ñ״����Դϴ�. �����ؾ� �մϴ�. ���� -16
					stf->Put(buffer, readBytes - 16);

					//����
					stf->MessageEnd();
					delete fileSink;
					fileSource.close();

					break;
				}
			}
			catch(const CryptoPP::Exception& e){
				//��й�ȣ ���� �� ���ܰ� �߻��� ���ɼ��� ����
				Report rpt(false, "FAIL!, CHECK YOUR PASSWORD");
				return rpt;
			}
		}

		decryptProgress.join();
		decryptProgress.~thread();
	}
	catch (const CryptoPP::Exception& e)
	{
		Report rpt(false, e.what());
		return rpt;
	}
	catch (const char* s) {
		Report rpt(false, s);
		return rpt;
	}

	Report rpt(true);
	return rpt;
}