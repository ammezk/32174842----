#ifndef COMMANDER_OF_ENDECRYPTER_H
#define COMMANDER_OF_ENDECRYPTER_H

#include<string>
using namespace std;
using std::string;

#include"Logger.h"
#include"Endecrypter.h"
#include"Report.h""

/*
해당 파일은 암복호화기 클래스가 가지고 있는 기능을
일관된 형식으로 외부에 제공해주기 위한 커맨드 클래스를
정의하고 있는 헤더 파일입니다.

Commander_of_Endecrypter는 외부에 일관된 형식으로
암복호화기의 기능을 제공하여, 기능을 요청하는 쪽(유저 인터페이스 모듈)과
기능을 수행하는 쪽(암복호화기)분리시키고 변경에 대해 독립성을 가질 수 있도록 합니다.

또한 로그 객체를 가지고 있어, 어떤 요청이 들어와서 기능을 요청하거나
요청된 작업이 실패 혹은 성공하거나 하는 사항들을 기록할 수 있습니다.
*/

class Commander_of_Endecrypter {
private:
	Endecrypter* endecrypter;

public:
	Commander_of_Endecrypter() { endecrypter = new Endecrypter(); }

	/*1. 암호화 기능 제공 인터페이스*/
	string encrypt(string targetPath, string destinationPath, string password1, string password2);

	/*2. 복호화 기능 제공 인터페이스*/
	string decrypt(string targetPath, string destinationPath, string password1, string password2);

	~Commander_of_Endecrypter() { delete endecrypter; }
};

#endif