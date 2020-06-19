#ifndef CONCRETEPAGES_H
#define CONCRETEPAGES_H

#include"ConsoleUI.h"
/*
Concrete Pages
�� �ܰ踦 �Լ��� �����ϰ� �� �Լ��� stepContainer�� �ʱ�ȭ�ϴ� 
���� Ŭ�����Դϴ�.

��� UI ��ҵ��� �����ϰ� �����ؾ��մϴ�.(Cpncrete Branches, Concrete Pages)
���� �̱��� ������ �̿��Ͽ� �����ϰ� ������ �� �ֵ��� �����߽��ϴ�.

���� �б� ��ҿ��� ���� EncryptionPage, DecryptionPage, ShowLogPage, DeleteLogPage�� �� ����
�� �ֽ��ϴ�.���ο� ���� ������ Ŭ������ ���������ν� �ܼ� ���� �������̽���
�����ϰ� Ȯ���� �� �ֽ��ϴ�.
*/


//EncryptionPage: ��ȣȭ �� ����ڿ��� �ܰ踦 ����
class EncryptionPage : public Page {
private:
	//��ȣȭ ��� ȣ�� �� �Ѱ��� ������
	string targetPath;
	string destinationPath;
	string password1, password2;

	//�ܺο��� ����� EncryptionPage��ü�� �������� ���ϰ� ����� ���ؼ�
	//��� �����ڴ� private�Դϴ�.
	EncryptionPage();
	EncryptionPage(EncryptionPage&) : Page() {}
	static EncryptionPage uniqueEncryptionPage;

protected:
	void is_final() {/*�� Ŭ������ ���� Ŭ������ �� �̻� Ȯ������ �ʽ��ϴ�.*/ }

public:
	//�ܺο� �ڱ��ڽſ� ���� ������ �����մϴ�.
	static EncryptionPage& getEncryptionPage() { return uniqueEncryptionPage; }
	virtual ~EncryptionPage() {}

	/*Steps*/
	static DIRECTION requestTargetPath();
	static DIRECTION requestDestinationPath();
	static DIRECTION requestPassword1();
	static DIRECTION requestPassword2();
	static DIRECTION showWarning();
	static DIRECTION requestEncryption();
};





//DecryptionPage: ��ȣȭ �� ����ڿ��� �ܰ踦 ����
class DecryptionPage : public Page {
private:
	//��ȣȭ ��� ȣ�� �� �Ѱ��� ������
	string targetPath;
	string destinationPath;
	string password1, password2;

	//�ܺο��� ����� DecryptionPage��ü�� �������� ���ϰ� ����� ���ؼ�
	//��� �����ڴ� private�Դϴ�.
	DecryptionPage();
	DecryptionPage(DecryptionPage&) : Page() {}
	static DecryptionPage uniqueDecryptionPage;

protected:
	void is_final() {/*�� Ŭ������ ���� Ŭ������ �� �̻� Ȯ������ �ʽ��ϴ�.*/ }

public:
	//�ܺο� �ڱ��ڽſ� ���� ������ �����մϴ�.
	static DecryptionPage& getDecryptionPage() { return uniqueDecryptionPage; }
	virtual ~DecryptionPage() {}

	/*Steps*/
	static DIRECTION requestTargetPath();
	static DIRECTION requestDestinationPath();
	static DIRECTION requestPassword1();
	static DIRECTION requestPassword2();
	static DIRECTION showWarning();
	static DIRECTION requestDecryption();
};



//ShowLogPage: ����ڿ��� �α� ������ ������
class ShowLogPage : Page {
private:
	//�ܺο��� ����� DecryptionPage��ü�� �������� ���ϰ� ����� ���ؼ�
	//��� �����ڴ� private�Դϴ�.
	ShowLogPage();
	ShowLogPage(ShowLogPage&) : Page() {}
	static ShowLogPage uniqueShowLogPage;

protected:
	void is_final() {/*�� Ŭ������ ���� Ŭ������ �� �̻� Ȯ������ �ʽ��ϴ�.*/ }

public:
	//�ܺο� �ڱ��ڽſ� ���� ������ �����մϴ�.
	static ShowLogPage& getShowLogPage() { return uniqueShowLogPage; }
	virtual ~ShowLogPage() {}

	/*Steps*/
	static DIRECTION requestLog();
};

//DeleteLogPage: �α� ������ �ʱ�ȭ�մϴ�.
class DeleteLogPage : Page {
private:
	//�ܺο��� ����� DecryptionPage��ü�� �������� ���ϰ� ����� ���ؼ�
	//��� �����ڴ� private�Դϴ�.
	DeleteLogPage();
	DeleteLogPage(DeleteLogPage&) : Page() {}
	static DeleteLogPage uniqueDeleteLogPage;

protected:
	void is_final() {/*�� Ŭ������ ���� Ŭ������ �� �̻� Ȯ������ �ʽ��ϴ�.*/ }

public:
	//�ܺο� �ڱ��ڽſ� ���� ������ �����մϴ�.
	static DeleteLogPage& getDeleteLogPage() { return uniqueDeleteLogPage; }
	virtual ~DeleteLogPage() {}

	/*Steps*/
	static DIRECTION requestLogDeletion();
};
#endif