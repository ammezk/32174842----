#include"ConcretePages.h"
#include"Console_IO_Forms.h"
#include"Commander_of_Endecrypter.h"
#include"Logger.h"

/*
�� ���� �������� ������, �ܰ迡 �ش��ϴ� �Լ���
stepContainer�� �ֽ��ϴ�.
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
//���� ��� ��ü �ν��Ͻ� ����
EncryptionPage EncryptionPage::uniqueEncryptionPage;

/*EncryptionPage Steps*/
/*	����ڷ� ���� ��ȣȭ ��� ���� ��θ� �Է� �޽��ϴ�.(�ִ�260����Ʈ ����)
	���� �ش� ��ΰ� �������� �ʰų� ���ٱ����� ������ ����ڿ���
	�˸��� �ٽ� �Է��� ��û�մϴ�.	*/
Page::DIRECTION EncryptionPage::requestTargetPath() {
	//����� �Է� ��
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
				//������ ���� �Ϳ� �����߽��ϴ�. ��ȿ�� ���� ���
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

/*	����ڷ� ���� ��ȣȭ ������ �� ��θ� �Է� �޽��ϴ�.
	���� �ش� ��ΰ� �������� �ʰų� ���ٱ����� ������ ����ڿ���
	�˸��� �ٽ� �Է��� ��û�մϴ�.	*/
Page::DIRECTION EncryptionPage::requestDestinationPath() {
	//���� ��� �Է� ��
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
				//������ ���� �Ϳ� �����߽��ϴ�. ��ȿ�� ���� ���
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

	/*����ڷ� ���� ��й�ȣ�� �Է¹޽��ϴ�.
	��й�ȣ�� �ּ� 8�� ~ �ִ� 20�� �̳��� �Է��մϴ�.*/
Page::DIRECTION EncryptionPage::requestPassword1() {
	//��й�ȣ �Է� ��
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

	/*����ڷ� ���� 2�� ��й�ȣ�� �Է¹޽��ϴ�.
	��й�ȣ�� �ּ� 8�� ~ �ִ� 20�� �̳� �����ϸ�
	1�� ��й�ȣ�� �޶�� �մϴ�.*/
Page::DIRECTION EncryptionPage::requestPassword2() {
	//��й�ȣ �Է� ��
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

	//Ŀ�Ǵ��� ����
	Commander_of_Endecrypter cmd;
	string msg = cmd.encrypt(EncryptionPage::getEncryptionPage().targetPath,
							EncryptionPage::getEncryptionPage().destinationPath,
							EncryptionPage::getEncryptionPage().password1,
							EncryptionPage::getEncryptionPage().password2);

	//��� ���
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
//���� ��� ��ü �ν��Ͻ� ����
DecryptionPage DecryptionPage::uniqueDecryptionPage;

/*DecryptionPage Steps*/
/*	����ڷ� ���� ��ȣȭ ��� ���� ��θ� �Է� �޽��ϴ�.
	���� �ش� ��ΰ� �������� �ʰų� ���ٱ����� ������ ����ڿ���
	�˸��� �ٽ� �Է��� ��û�մϴ�.	*/
Page::DIRECTION DecryptionPage::requestTargetPath() {
	//����� �Է� ��
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
				//������ ���� �Ϳ� �����߽��ϴ�. ��ȿ�� ���� ���
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

/*	����ڷ� ���� ��ȣȭ ������ �� ��θ� �Է� �޽��ϴ�.
	���� �ش� ��ΰ� �������� �ʰų� ���ٱ����� ������ ����ڿ���
	�˸��� �ٽ� �Է��� ��û�մϴ�.	*/
Page::DIRECTION DecryptionPage::requestDestinationPath() {
	//���� ��� �Է� ��
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
				//������ ���� �Ϳ� �����߽��ϴ�. ��ȿ�� ���� ���
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

/*����ڷ� ���� ��й�ȣ�� �Է¹޽��ϴ�.
��й�ȣ�� �ּ� 8�� ~ �ִ� 20�� �̳��� �Է��մϴ�.*/
Page::DIRECTION DecryptionPage::requestPassword1() {
	//��й�ȣ �Է� ��
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

	/*����ڷ� ���� 2�� ��й�ȣ�� �Է¹޽��ϴ�.
	��й�ȣ�� �ּ� 8�� ~ �ִ� 20�� �̳� �����ϸ�
	1�� ��й�ȣ�� �޶�� �մϴ�.*/
Page::DIRECTION DecryptionPage::requestPassword2() {
	//��й�ȣ �Է� ��
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
	//Ŀ�Ǵ��� ����
	cout << "Decrypting...\n";

	//Ŀ�Ǵ��� ����
	Commander_of_Endecrypter cmd;
	string msg = cmd.decrypt(DecryptionPage::getDecryptionPage().targetPath,
		DecryptionPage::getDecryptionPage().destinationPath,
		DecryptionPage::getDecryptionPage().password1,
		DecryptionPage::getDecryptionPage().password2);

	//��� ���
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
//���� ��� ����
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
//���� ��� ����
DeleteLogPage DeleteLogPage::uniqueDeleteLogPage;

Page::DIRECTION DeleteLogPage::requestLogDeletion() {
	Logger::reset();
	cout << "Log reset\n";
	system("pause");

	return DIRECTION::NEXT;
}
/*==========================================*/