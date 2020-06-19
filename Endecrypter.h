#ifndef ENDECRYPTER_H
#define ENDECRYPTER_H

#include<fstream>
using namespace std;
using std::ofstream;

#include"Report.h"

/*
암호화 및 복호화를 수행하는 암복호화기 클래스입니다.
crypto++ 라이브러리를 이용하여 암호화 및 복호화 기능을 구현하였습니다.
scrypt 알고리즘을 이용하여 비밀번호를 key과 IV로 변환한 후
AES 알고리즘을 CBC 블록 모드로 수행하여 암호화 혹은 복호화 합니다.
*/
class Endecrypter {
private:
public:
	//암호화를 수행하는 함수입니다.
	//암호화할 대상 파일 경로, 암호화 하여 저장할 목적 파일 경로, 1차 2차 비밀번호를 받아서 암호화를 수행합니다.
	Report encrypt(const char* targetFilePath, const char* destinationPath, const char* password1, const char* password2);

	//복호화를 수행하는 함수입니다.
	//복호화할 대상 파일 경로, 복호화 하여 저장할 목적 파일 경로, 1차 2차 비밀번호를 받아서 복호화를 수행합니다.
	Report decrypt(const char* targetFilePath, const char* destinationPath, const char* password1, const char* password2);
};

//암호화, 복호화 시 사용자에게 진행도를 보여주는 함수입니다.
//별도의 스레드를 통해서 실행되어야 합니다.
void showProgress(ostream* ofs, long size, const char* filePath);

#endif