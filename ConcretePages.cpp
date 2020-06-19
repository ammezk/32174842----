#include"ConcretePages.h"
#include"Console_IO_Forms.h"
#include"Commander_of_Endecrypter.h"
#include"Logger.h"

/*
각 구상 페이지에 구현된, 단계에 해당하는 함수를
stepContainer에 넣습니다.
*/

/*==========Encryption Page==========*/
#include<fstream>
using std::ifstream;
using std::ofstream;

EncryptionPage::EncryptionPage() {
	description = "Encryption";
	stepContainer->push_back(requestTargetPath);
	stepContainer->push_back(requestDestinationPath);
	stepContainer->push_back(requestPassword1);
	stepContainer->push_back(requestPassword2);
	stepContainer->push_back(showWarning);
	stepContainer->push_back(requestEncryption);
}
//정적 멤버 객체 인스턴스 생성
EncryptionPage EncryptionPage::uniqueEncryptionPage;

/*EncryptionPage Steps*/
/*	사용자로 부터 암호화 대상 파일 경로를 입력 받습니다.(최대260바이트 길이)
	만약 해당 경로가 존재하지 않거나 접근권한이 없으면 사용자에게
	알리고 다시 입력을 요청합니다.	*/
Page::DIRECTION EncryptionPage::requestTargetPath() {
	//대상경로 입력 폼
	string targetPath;
	while (true) {
		try {
			lineInputForm("Input The target path >> ", targetPath);
			ifstream targetFile(targetPath, ios::in | ios::binary);
			if (!targetFile) {
				cout << "\x1b[A"; clearLine();
				cout << "Cannot open the file, re-";
				continue;
			}
			else {
				//파일을 여는 것에 성공했습니다. 유효한 파일 경로
				targetFile.close();
				EncryptionPage::getEncryptionPage().targetPath = targetPath;
				break;
			}
		}
		catch (const char* msg) {
			cout << "\x1b[A"; clearLine();
		}
	}

	return Page::whichDir();
}

/*	사용자로 부터 암호화 파일을 쓸 경로를 입력 받습니다.
	만약 해당 경로가 존재하지 않거나 접근권한이 없으면 사용자에게
	알리고 다시 입력을 요청합니다.	*/
Page::DIRECTION EncryptionPage::requestDestinationPath() {
	//목적 경로 입력 폼
	string destinationPath;
	while (true) {
		try {
			lineInputForm("Input The destination path >> ", destinationPath);
			ofstream destFile(destinationPath , ios::ate | ios::binary);
			if (!destFile) {
				cout << "\x1b[A"; clearLine();
				cout << "Cannot open the file, re-";
				continue;
			}
			else {
				//파일을 여는 것에 성공했습니다. 유효한 파일 경로
				destFile.close();
				EncryptionPage::getEncryptionPage().destinationPath = destinationPath;
				break;
			}
		}
		catch (const char* msg) {
			cout << "\x1b[A"; clearLine();
		}
	}

	return Page::whichDir();
}

	/*사용자로 부터 비밀번호를 입력받습니다.
	비밀번호는 최소 8자 ~ 최대 20자 이내로 입력합니다.*/
Page::DIRECTION EncryptionPage::requestPassword1() {
	//비밀번호 입력 폼
	string password1;
	while (true) {
		try {
			lineInputForm("Input The password, At least 8 characters most 20 characters >> ", password1);
			if (password1.size() < 8 || password1.size() > 20) {
				cout << "\x1b[A"; clearLine();
				continue;
			}
			else {
				EncryptionPage::getEncryptionPage().password1 = password1;
				break;
			}
		}
		catch (const char* msg) {
			cout << "\x1b[A"; clearLine();
		}
	}

	return Page::whichDir();
}

	/*사용자로 부터 2차 비밀번호를 입력받습니다.
	비밀번호는 최소 8자 ~ 최대 20자 이내 여야하며
	1차 비밀번호와 달라야 합니다.*/
Page::DIRECTION EncryptionPage::requestPassword2() {
	//비밀번호 입력 폼
	string password2;
	while (true) {
		try {
			lineInputForm("Input The 2nd password, At least 8 characters most 20 characters >> ", password2);
			if (password2.size() < 8 || password2.size() > 20) {
				cout << "\x1b[A"; clearLine();
				continue;
			}
			else if (password2 == EncryptionPage::getEncryptionPage().password1) {
				cout << "\x1b[A"; clearLine();
				continue;
			}
			else {
				EncryptionPage::getEncryptionPage().password2 = password2;
				break;
			}
		}
		catch (const char* msg) {
			cout << "\x1b[A"; clearLine();
		}
	}

	return Page::whichDir();
}

Page::DIRECTION EncryptionPage::showWarning() {
	cout << "Warning! If you forget the passwords the file will be Encrypted forever" << endl;
	cout << "Check thoroughly your passwords\n\n";

	cout << "***Target Path: " << EncryptionPage::getEncryptionPage().targetPath << endl;
	cout << "***Destination Path: " << EncryptionPage::getEncryptionPage().destinationPath << endl;
	cout << "***1st password: " << EncryptionPage::getEncryptionPage().password1 << endl;
	cout << "***2nd password: " << EncryptionPage::getEncryptionPage().password2 << endl;

	cout << endl;

	return Page::whichDir();
}
Page::DIRECTION EncryptionPage::requestEncryption() {
	cout << "Encrypting...\n";

	//커맨더와 연결
	Commander_of_Endecrypter cmd;
	string msg = cmd.encrypt(EncryptionPage::getEncryptionPage().targetPath,
							EncryptionPage::getEncryptionPage().destinationPath,
							EncryptionPage::getEncryptionPage().password1,
							EncryptionPage::getEncryptionPage().password2);

	//결과 출력
	cout << endl << msg << endl;
	system("pause");

	return DIRECTION::NEXT;
}
/*===================================*/










/*==========Decryption Page==========*/
#include<fstream>
using std::ifstream;
using std::ofstream;

DecryptionPage::DecryptionPage() {
	description = "Decryption";
	stepContainer->push_back(requestTargetPath);
	stepContainer->push_back(requestDestinationPath);
	stepContainer->push_back(requestPassword1);
	stepContainer->push_back(requestPassword2);
	stepContainer->push_back(showWarning);
	stepContainer->push_back(requestDecryption);
}
//정적 멤버 객체 인스턴스 생성
DecryptionPage DecryptionPage::uniqueDecryptionPage;

/*DecryptionPage Steps*/
/*	사용자로 부터 암호화 대상 파일 경로를 입력 받습니다.
	만약 해당 경로가 존재하지 않거나 접근권한이 없으면 사용자에게
	알리고 다시 입력을 요청합니다.	*/
Page::DIRECTION DecryptionPage::requestTargetPath() {
	//대상경로 입력 폼
	string targetPath;
	while (true) {
		try {
			lineInputForm("Input The target path >> ", targetPath);
			ifstream targetFile(targetPath, ios::in | ios::binary);
			if (!targetFile) {
				cout << "\x1b[A"; clearLine();
				cout << "Cannot open the file, re-";
				continue;
			}
			else {
				//파일을 여는 것에 성공했습니다. 유효한 파일 경로
				targetFile.close();
				DecryptionPage::getDecryptionPage().targetPath = targetPath;
				break;
			}
		}
		catch (const char* msg) {
			cout << "\x1b[A"; clearLine();
		}
	}

	return Page::whichDir();
}

/*	사용자로 부터 암호화 파일을 쓸 경로를 입력 받습니다.
	만약 해당 경로가 존재하지 않거나 접근권한이 없으면 사용자에게
	알리고 다시 입력을 요청합니다.	*/
Page::DIRECTION DecryptionPage::requestDestinationPath() {
	//목적 경로 입력 폼
	string destinationPath;
	while (true) {
		try {
			lineInputForm("Input The destination path >> ", destinationPath);
			ofstream destFile(destinationPath, ios::ate | ios::binary);
			if (!destFile) {
				cout << "\x1b[A"; clearLine();
				cout << "Cannot open the file, re-";
				continue;
			}
			else {
				//파일을 여는 것에 성공했습니다. 유효한 파일 경로
				destFile.close();
				DecryptionPage::getDecryptionPage().destinationPath = destinationPath;
				break;
			}
		}
		catch (const char* msg) {
			cout << "\x1b[A"; clearLine();
		}
	}

	return Page::whichDir();
}

/*사용자로 부터 비밀번호를 입력받습니다.
비밀번호는 최소 8자 ~ 최대 20자 이내로 입력합니다.*/
Page::DIRECTION DecryptionPage::requestPassword1() {
	//비밀번호 입력 폼
	string password1;
	while (true) {
		try {
			lineInputForm("Input The password, At least 8 characters most 20 characters >> ", password1);
			if (password1.size() < 8 || password1.size() > 20) {
				cout << "\x1b[A"; clearLine();
				continue;
			}
			else {
				DecryptionPage::getDecryptionPage().password1 = password1;
				break;
			}
		}
		catch (const char* msg) {
			cout << "\x1b[A"; clearLine();
		}
	}

	return Page::whichDir();
}

	/*사용자로 부터 2차 비밀번호를 입력받습니다.
	비밀번호는 최소 8자 ~ 최대 20자 이내 여야하며
	1차 비밀번호와 달라야 합니다.*/
Page::DIRECTION DecryptionPage::requestPassword2() {
	//비밀번호 입력 폼
	string password2;
	while (true) {
		try {
			lineInputForm("Input The 2nd password, At least 8 characters most 20 characters >> ", password2);
			if (password2.size() < 8 || password2.size() > 20) {
				cout << "\x1b[A"; clearLine();
				continue;
			}
			else if (password2 == DecryptionPage::getDecryptionPage().password1) {
				cout << "\x1b[A"; clearLine();
				continue;
			}
			else {
				DecryptionPage::getDecryptionPage().password2 = password2;
				break;
			}
		}
		catch (const char* msg) {
			cout << "\x1b[A"; clearLine();
		}
	}

	return Page::whichDir();
}

Page::DIRECTION DecryptionPage::showWarning() {
	cout << "Warning! If your password is wrong, the result file could be incorrectly decrypted" << endl;
	cout << "Check your passwords once more\n\n";

	cout << "***Target Path: " << DecryptionPage::getDecryptionPage().targetPath << endl;
	cout << "***Destination Path: " << DecryptionPage::getDecryptionPage().destinationPath << endl;
	cout << "***1st password: " << DecryptionPage::getDecryptionPage().password1 << endl;
	cout << "***2nd password: " << DecryptionPage::getDecryptionPage().password2 << endl;

	cout << endl;

	return Page::whichDir();
}
Page::DIRECTION DecryptionPage::requestDecryption() {
	//커맨더와 연결
	cout << "Decrypting...\n";

	//커맨더와 연결
	Commander_of_Endecrypter cmd;
	string msg = cmd.decrypt(DecryptionPage::getDecryptionPage().targetPath,
		DecryptionPage::getDecryptionPage().destinationPath,
		DecryptionPage::getDecryptionPage().password1,
		DecryptionPage::getDecryptionPage().password2);

	//결과 출력
	cout << endl << msg << endl;
	system("pause");

	return DIRECTION::NEXT;
}
/*===================================*/










/*==============ShowLog Page==============*/
ShowLogPage::ShowLogPage() {
	description = "Show log";
	stepContainer->push_back(requestLog);
}
//정적 멤버 변수
ShowLogPage ShowLogPage::uniqueShowLogPage;

Page::DIRECTION ShowLogPage::requestLog() {
	Logger::showLog();
	system("pause");

	return DIRECTION::NEXT;
}
/*========================================*/




/*==============DeleteLog Page==============*/
DeleteLogPage::DeleteLogPage() {
	description = "Delete log";
	stepContainer->push_back(requestLogDeletion);
}
//정적 멤버 변수
DeleteLogPage DeleteLogPage::uniqueDeleteLogPage;

Page::DIRECTION DeleteLogPage::requestLogDeletion() {
	Logger::reset();
	cout << "Log reset\n";
	system("pause");

	return DIRECTION::NEXT;
}
/*==========================================*/