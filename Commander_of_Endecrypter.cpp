#include"Commander_of_Endecrypter.h"

#include<iostream>
using namespace std;

/*1. 암호화 기능 제공 인터페이스*/
string Commander_of_Endecrypter::encrypt(string targetPath, string destinationPath, string password1, string password2) {
	//암호화 시작 로깅
	Logger::log(LOG_MACRO::ENCRYPTION_START, targetPath + "--->" + destinationPath);
	Report rpt;

	rpt = endecrypter->encrypt(targetPath.c_str(), destinationPath.c_str(), password1.c_str(), password2.c_str());

	//암호화 성공
	if (rpt.is_success) {
		Logger::log(LOG_MACRO::ENCRYPTION_SUCCESS, targetPath + "--->" + destinationPath);
		return "ENCRYPTION COMPLETE!";
	}
	//암호화 실패
	else {
		Logger::log(LOG_MACRO::ENCRYPTION_FAILURE, targetPath + "--->" + destinationPath);
		return rpt.msg;
	}
}

/*2. 복호화 기능 제공 인터페이스*/
string Commander_of_Endecrypter::decrypt(string targetPath, string destinationPath, string password1, string password2) {
	//복호화 시작 로깅
	Logger::log(LOG_MACRO::DECRYPTION_START, targetPath + "--->" + destinationPath);
	Report rpt;

	rpt = endecrypter->decrypt(targetPath.c_str(), destinationPath.c_str(), password1.c_str(), password2.c_str());

	//암호화 성공
	if (rpt.is_success) {
		Logger::log(LOG_MACRO::DECRYPTION_SUCCESS, targetPath + "--->" + destinationPath);
		return "DECRYPTION COMPLETE!";
	}
	//암호화 실패
	else {
		Logger::log(LOG_MACRO::DECRYPTION_FAILURE, targetPath + "--->" + destinationPath);
		return rpt.msg;
	}
}
