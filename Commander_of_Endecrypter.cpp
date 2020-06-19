#include"Commander_of_Endecrypter.h"

#include<iostream>
using namespace std;

/*1. ��ȣȭ ��� ���� �������̽�*/
string Commander_of_Endecrypter::encrypt(string targetPath, string destinationPath, string password1, string password2) {
	//��ȣȭ ���� �α�
	Logger::log(LOG_MACRO::ENCRYPTION_START, targetPath + "--->" + destinationPath);
	Report rpt;

	rpt = endecrypter->encrypt(targetPath.c_str(), destinationPath.c_str(), password1.c_str(), password2.c_str());

	//��ȣȭ ����
	if (rpt.is_success) {
		Logger::log(LOG_MACRO::ENCRYPTION_SUCCESS, targetPath + "--->" + destinationPath);
		return "ENCRYPTION COMPLETE!";
	}
	//��ȣȭ ����
	else {
		Logger::log(LOG_MACRO::ENCRYPTION_FAILURE, targetPath + "--->" + destinationPath);
		return rpt.msg;
	}
}

/*2. ��ȣȭ ��� ���� �������̽�*/
string Commander_of_Endecrypter::decrypt(string targetPath, string destinationPath, string password1, string password2) {
	//��ȣȭ ���� �α�
	Logger::log(LOG_MACRO::DECRYPTION_START, targetPath + "--->" + destinationPath);
	Report rpt;

	rpt = endecrypter->decrypt(targetPath.c_str(), destinationPath.c_str(), password1.c_str(), password2.c_str());

	//��ȣȭ ����
	if (rpt.is_success) {
		Logger::log(LOG_MACRO::DECRYPTION_SUCCESS, targetPath + "--->" + destinationPath);
		return "DECRYPTION COMPLETE!";
	}
	//��ȣȭ ����
	else {
		Logger::log(LOG_MACRO::DECRYPTION_FAILURE, targetPath + "--->" + destinationPath);
		return rpt.msg;
	}
}
