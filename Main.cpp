#include"ConsoleUI.h"
#include"ConcreteBranches.h"
#include"Logger.h"

#include<iostream>
using namespace std;

//FileLocker ������
int main() {
	//�α� �˻�
	Logger::scan();

	//���α׷� ����
	Logger::log(LOG_MACRO::PROGRAM_START);

	//�������̽� ���
	Branch* mainMenu = &MainBranch::getMainBranch();
	mainMenu->representComponent();

	//���α׷� ���� ����
	Logger::log(LOG_MACRO::PROGRAM_END_PROPERLY);
	system("pause");

	return 0;
}