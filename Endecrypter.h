#ifndef ENDECRYPTER_H
#define ENDECRYPTER_H

#include<fstream>
using namespace std;
using std::ofstream;

#include"Report.h"

/*
��ȣȭ �� ��ȣȭ�� �����ϴ� �Ϻ�ȣȭ�� Ŭ�����Դϴ�.
crypto++ ���̺귯���� �̿��Ͽ� ��ȣȭ �� ��ȣȭ ����� �����Ͽ����ϴ�.
scrypt �˰����� �̿��Ͽ� ��й�ȣ�� key�� IV�� ��ȯ�� ��
AES �˰����� CBC ��� ���� �����Ͽ� ��ȣȭ Ȥ�� ��ȣȭ �մϴ�.
*/
class Endecrypter {
private:
public:
	//��ȣȭ�� �����ϴ� �Լ��Դϴ�.
	//��ȣȭ�� ��� ���� ���, ��ȣȭ �Ͽ� ������ ���� ���� ���, 1�� 2�� ��й�ȣ�� �޾Ƽ� ��ȣȭ�� �����մϴ�.
	Report encrypt(const char* targetFilePath, const char* destinationPath, const char* password1, const char* password2);

	//��ȣȭ�� �����ϴ� �Լ��Դϴ�.
	//��ȣȭ�� ��� ���� ���, ��ȣȭ �Ͽ� ������ ���� ���� ���, 1�� 2�� ��й�ȣ�� �޾Ƽ� ��ȣȭ�� �����մϴ�.
	Report decrypt(const char* targetFilePath, const char* destinationPath, const char* password1, const char* password2);
};

//��ȣȭ, ��ȣȭ �� ����ڿ��� ���൵�� �����ִ� �Լ��Դϴ�.
//������ �����带 ���ؼ� ����Ǿ�� �մϴ�.
void showProgress(ostream* ofs, long size, const char* filePath);

#endif