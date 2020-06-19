#include"ConcreteBranches.h"
#include"ConcretePages.h"

/*===============MainBranch===============*/
/*
������, 
Concrete Branch��� Concrete Page���� �����Ͽ�
Branch�� componentContainer�� �ʱ�ȭ �մϴ�.
*/
MainBranch::MainBranch() : Branch(){
	description = "Main Menu";
	/*1. Encryption*/componentContainer->push_back(&(EncryptionPage::getEncryptionPage()));
	/*2. Decryption*/componentContainer->push_back(&(DecryptionPage::getDecryptionPage()));
	/*3. Print Log*/componentContainer->push_back(&(LogBranch::getLogBranch()));
}
//���� ��� ���� �ʱ�ȭ
MainBranch MainBranch::uniqueMainBranch;
/*=========================================*/




/*===============Log Branch=============*/
LogBranch::LogBranch() : Branch() {
	description = "Log Menu";
	/*1. Show log*/		componentContainer->push_back((Component*)&(ShowLogPage::getShowLogPage()));
	/*2. Delete log*/	componentContainer->push_back((Component*)&(DeleteLogPage::getDeleteLogPage()));
}
//���� ��� ���� �ʱ�ȭ
LogBranch LogBranch::uniqueLogBranch;
/*======================================*/