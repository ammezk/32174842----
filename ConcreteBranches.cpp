#include"ConcreteBranches.h"
#include"ConcretePages.h"

/*===============MainBranch===============*/
/*
생성자, 
Concrete Branch들과 Concrete Page들을 생성하여
Branch의 componentContainer를 초기화 합니다.
*/
MainBranch::MainBranch() : Branch(){
	description = "Main Menu";
	/*1. Encryption*/componentContainer->push_back(&(EncryptionPage::getEncryptionPage()));
	/*2. Decryption*/componentContainer->push_back(&(DecryptionPage::getDecryptionPage()));
	/*3. Print Log*/componentContainer->push_back(&(LogBranch::getLogBranch()));
}
//정적 멤버 변수 초기화
MainBranch MainBranch::uniqueMainBranch;
/*=========================================*/




/*===============Log Branch=============*/
LogBranch::LogBranch() : Branch() {
	description = "Log Menu";
	/*1. Show log*/		componentContainer->push_back((Component*)&(ShowLogPage::getShowLogPage()));
	/*2. Delete log*/	componentContainer->push_back((Component*)&(DeleteLogPage::getDeleteLogPage()));
}
//정적 멤버 변수 초기화
LogBranch LogBranch::uniqueLogBranch;
/*======================================*/