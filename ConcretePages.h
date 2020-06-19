#ifndef CONCRETEPAGES_H
#define CONCRETEPAGES_H

#include"ConsoleUI.h"
/*
Concrete Pages
각 단계를 함수로 정의하고 그 함수로 stepContainer를 초기화하는 
구상 클래스입니다.

모든 UI 요소들은 유일하게 존재해야합니다.(Cpncrete Branches, Concrete Pages)
따라서 싱글턴 패턴을 이용하여 유일하게 존재할 수 있도록 구현했습니다.

구성 분기 요소에는 현재 EncryptionPage, DecryptionPage, ShowLogPage, DeleteLogPage의 네 가지
가 있습니다.새로운 구상 페이지 클래스를 정의함으로써 콘솔 유저 인터페이스를
용이하게 확장할 수 있습니다.
*/


//EncryptionPage: 암호화 시 사용자에게 단계를 제시
class EncryptionPage : public Page {
private:
	//암호화 기능 호출 시 넘겨줄 데이터
	string targetPath;
	string destinationPath;
	string password1, password2;

	//외부에서 맘대로 EncryptionPage객체를 생성하지 못하게 만들기 위해서
	//모든 생성자는 private입니다.
	EncryptionPage();
	EncryptionPage(EncryptionPage&) : Page() {}
	static EncryptionPage uniqueEncryptionPage;

protected:
	void is_final() {/*이 클래스는 구상 클래스로 더 이상 확장하지 않습니다.*/ }

public:
	//외부에 자기자신에 대한 참조를 제공합니다.
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





//DecryptionPage: 복호화 시 사용자에게 단계를 제시
class DecryptionPage : public Page {
private:
	//암호화 기능 호출 시 넘겨줄 데이터
	string targetPath;
	string destinationPath;
	string password1, password2;

	//외부에서 맘대로 DecryptionPage객체를 생성하지 못하게 만들기 위해서
	//모든 생성자는 private입니다.
	DecryptionPage();
	DecryptionPage(DecryptionPage&) : Page() {}
	static DecryptionPage uniqueDecryptionPage;

protected:
	void is_final() {/*이 클래스는 구상 클래스로 더 이상 확장하지 않습니다.*/ }

public:
	//외부에 자기자신에 대한 참조를 제공합니다.
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



//ShowLogPage: 사용자에게 로그 정보를 보여줌
class ShowLogPage : Page {
private:
	//외부에서 맘대로 DecryptionPage객체를 생성하지 못하게 만들기 위해서
	//모든 생성자는 private입니다.
	ShowLogPage();
	ShowLogPage(ShowLogPage&) : Page() {}
	static ShowLogPage uniqueShowLogPage;

protected:
	void is_final() {/*이 클래스는 구상 클래스로 더 이상 확장하지 않습니다.*/ }

public:
	//외부에 자기자신에 대한 참조를 제공합니다.
	static ShowLogPage& getShowLogPage() { return uniqueShowLogPage; }
	virtual ~ShowLogPage() {}

	/*Steps*/
	static DIRECTION requestLog();
};

//DeleteLogPage: 로그 파일을 초기화합니다.
class DeleteLogPage : Page {
private:
	//외부에서 맘대로 DecryptionPage객체를 생성하지 못하게 만들기 위해서
	//모든 생성자는 private입니다.
	DeleteLogPage();
	DeleteLogPage(DeleteLogPage&) : Page() {}
	static DeleteLogPage uniqueDeleteLogPage;

protected:
	void is_final() {/*이 클래스는 구상 클래스로 더 이상 확장하지 않습니다.*/ }

public:
	//외부에 자기자신에 대한 참조를 제공합니다.
	static DeleteLogPage& getDeleteLogPage() { return uniqueDeleteLogPage; }
	virtual ~DeleteLogPage() {}

	/*Steps*/
	static DIRECTION requestLogDeletion();
};
#endif