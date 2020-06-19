#include"Logger.h"

#include<iostream>
using namespace std;
using std::cin;
using std::cout;

#include<fstream>
using std::ifstream;
using std::ofstream;

#include<ctime>
using std::tm;

//�α� ���� ���
string Logger::logFilePath = LOG_FILE_PATH;

/*1. �־��� �����͸� �޾Ƽ� ������ ���Ĵ�� �ؽ�Ʈ ���Ͽ� ����մϴ�.*/
void Logger::log(LOG_MACRO logMacro, string description) {
	//�ؽ�Ʈ ���� ������ ���� �ڿ� �߰��ϴ� �������� ���ϴ�.
	ofstream logFile(LOG_FILE_PATH, ios::app);
	if (!logFile) {
		throw "Cannot open log file!";
	}


	//����ð��� ���ڿ��� ��ȯ���� �����մϴ�.
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);

	string contents = to_string((newtime.tm_year + 1900)) + "-" + to_string((newtime.tm_mon + 1)) + "-" + to_string((newtime.tm_mday)) + ", "
		+ to_string((newtime.tm_hour)) + ":" + to_string((newtime.tm_min)) + ":" + to_string((newtime.tm_sec));

	contents += " | ";

	switch (logMacro) {
	case LOG_MACRO::ENCRYPTION_START:	contents += "@EncryptionStart | "; break;
	case LOG_MACRO::ENCRYPTION_SUCCESS:	contents += "@EncryptionSuccess | "; break;
	case LOG_MACRO::ENCRYPTION_FAILURE:	contents += "@EncryptionFailure | "; break;
	case LOG_MACRO::DECRYPTION_START:	contents += "@DecryptionStart | "; break;
	case LOG_MACRO::DECRYPTION_SUCCESS:	contents += "@DecryptionSuccess | "; break;
	case LOG_MACRO::DECRYPTION_FAILURE:	contents += "@DecryptionFailure | "; break;
	case LOG_MACRO::PROGRAM_START:		contents += "@START | "; break;
	case LOG_MACRO::PROGRAM_END_PROPERLY:contents += "@END | "; break;
	}

	contents += description + '\n';
	
	//�α� ������ �� �ٿ� �ִ� 200�� �����Դϴ�. �� �̻��� �Ǹ� description�� �Ϻΰ� �߸��ϴ�.
	logFile.write(contents.c_str(), contents.size());
}

//��ü �α׸� ����� �ݴϴ�.
void Logger::showLog() {
	ifstream logFile(LOG_FILE_PATH, ios::in);
	if (!logFile) {
		//������ ���� ��� �� �α� ������ ����ϴ�.
		//�ٸ� ������ ���� �� �ϴ� ��� ���ϳ����� �����Ǵ� ���� �������ؼ� ios::ate��带 ����մϴ�.
		ofstream temp(LOG_FILE_PATH, ios::ate);
		temp.close();

		//������ �ٽ� �н��ϴ�.
		logFile.open(LOG_FILE_PATH, ios::in);
		if (!logFile) {
			cout << "�α� ������ �� �� �����ϴ�!\n";
			return;
		}
	}

	char msg[200];
	while (!logFile.eof()) {
		logFile.getline(msg, 200);
		cout << msg << endl;
	}
}


/*3. ���Ϸ� ���� �����͸� �о ���� ���࿡���� ������ �������� Ȯ���մϴ�.*/
#include<stack>
#include<cstring>
void Logger::scan() {

	
	//�ؽ�Ʈ ���� ������ �н��ϴ�.
	ifstream logScanner(LOG_FILE_PATH, ios::in);
	if (!logScanner) {
		//������ ���� ��� �� �α� ������ ����ϴ�.
		//�ٸ� ������ ���� �� �ϴ� ��� ���ϳ����� �����Ǵ� ���� �������ؼ� ios::ate��带 ����մϴ�.
		ofstream temp(LOG_FILE_PATH, ios::ate);
		temp.close();

		//������ �ٽ� �н��ϴ�.
		logScanner.open(LOG_FILE_PATH, ios::in);
		if (!logScanner) {
			cout << "�α� ������ �� �� �����ϴ�!\n";
			return;
		}
	}

	//���� �α׵��� ����� ����
	stack<string> logStack;
	
	//���Ͽ� ������ ���� ��� �ٷ� ���������� @END�� �ʱ�ȭ �մϴ�.
	char buffer[200];

	//�α� ���Ͽ��� ��� ����� �о� ���ÿ� �ֽ��ϴ�.
	do {
		logScanner.getline(buffer, 200);
		logStack.push(buffer);
	} while (!logScanner.eof());
	
	//���� �ֱ� �α׺��� �ϳ��� �˻��մϴ�. ���� ó���� @END�� �����ٸ� �÷��װ� false�� ���Դϴ�.
	//���� ������ ����(���� �޴��� ������ ���� ����)�� ��� ó���� ������ @START�� ���� �˻�� ����˴ϴ�.
	//���� �ֱٽ��� ��� �˻簡 ���� �� flag�� �˻��Ͽ� true�� �׸��� �ִ� ��� 
	//������ ����� �ִµ�, ���� ����� ���� ���Դϴ�. ��,  ���α׷��� ���߿� ����� ���Դϴ�.
	string incompleteEncryption = "";
	string incompleteDecryption = "";
	string log;
	bool encrypt_flag = false;
	bool decrypt_flag = false;
	while (true) {
		if (logStack.size() == 0) { break; }

		log = logStack.top();
		logStack.pop();

		if (log.find("@END") != -1) { break; }
		else if (log.find("@EncryptionStart") != -1) {
			encrypt_flag = (encrypt_flag) ? false : true;
			if (incompleteEncryption == "")
				incompleteEncryption = log;
		}
		else if (log.find("@EncryptionSuccess") != -1) {
			encrypt_flag = (encrypt_flag) ? false : true;
		}
		else if (log.find("@EncryptionFailure") != -1) {
			encrypt_flag = (encrypt_flag) ? false : true;
		}
		else if (log.find("@DecryptionStart") != -1) {
			decrypt_flag = (decrypt_flag) ? false : true;
			if (incompleteDecryption == "")
				incompleteDecryption = log;
		}
		else if (log.find("@DecryptionSuccess") != -1) {
			decrypt_flag = (decrypt_flag) ? false : true;
		}
		else if (log.find("@DecryptionFailure") != -1) {
			decrypt_flag = (decrypt_flag) ? false : true;
		}
		else if (log.find("@START") != -1) { break; }
	}
	
	if (encrypt_flag) {
		cout << incompleteEncryption << endl;
		cout << "��ȣȭ ���߿� ������ ���� �ߴܵǾ������ϴ�." << endl;
	}
	if (decrypt_flag) {
		cout << incompleteDecryption << endl;
		cout << "��ȣȭ ���߿� ������ ���� �ߴܵǾ������ϴ�." << endl;
	}
	//������ �־��� �� ����ڰ� �޽����� ���� �� �ֵ��� ��ٷ����մϴ�.
	if (encrypt_flag | decrypt_flag) {
		system("PAUSE");
	}
	
	//��Ʈ���� �����ϰ�, �α����Ͽ� @END�� �ֽ��ϴ�.
	logScanner.close();
	Logger::log(LOG_MACRO::PROGRAM_END_PROPERLY);
}

/*4. �α� ����� �ʱ�ȭ�մϴ�.*/
void Logger::reset() {
	ofstream bloomstick(LOG_FILE_PATH, ios::trunc);
	if (!bloomstick) {
		throw "Cannot open log file";
	}
	bloomstick.close();
}