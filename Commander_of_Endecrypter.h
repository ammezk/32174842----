#ifndef COMMANDER_OF_ENDECRYPTER_H
#define COMMANDER_OF_ENDECRYPTER_H

#include<string>
using namespace std;
using std::string;

#include"Logger.h"
#include"Endecrypter.h"
#include"Report.h""

/*
�ش� ������ �Ϻ�ȣȭ�� Ŭ������ ������ �ִ� �����
�ϰ��� �������� �ܺο� �������ֱ� ���� Ŀ�ǵ� Ŭ������
�����ϰ� �ִ� ��� �����Դϴ�.

Commander_of_Endecrypter�� �ܺο� �ϰ��� ��������
�Ϻ�ȣȭ���� ����� �����Ͽ�, ����� ��û�ϴ� ��(���� �������̽� ���)��
����� �����ϴ� ��(�Ϻ�ȣȭ��)�и���Ű�� ���濡 ���� �������� ���� �� �ֵ��� �մϴ�.

���� �α� ��ü�� ������ �־�, � ��û�� ���ͼ� ����� ��û�ϰų�
��û�� �۾��� ���� Ȥ�� �����ϰų� �ϴ� ���׵��� ����� �� �ֽ��ϴ�.
*/

class Commander_of_Endecrypter {
private:
	Endecrypter* endecrypter;

public:
	Commander_of_Endecrypter() { endecrypter = new Endecrypter(); }

	/*1. ��ȣȭ ��� ���� �������̽�*/
	string encrypt(string targetPath, string destinationPath, string password1, string password2);

	/*2. ��ȣȭ ��� ���� �������̽�*/
	string decrypt(string targetPath, string destinationPath, string password1, string password2);

	~Commander_of_Endecrypter() { delete endecrypter; }
};

#endif