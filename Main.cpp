#include"ConsoleUI.h"
#include"ConcreteBranches.h"
#include"Logger.h"

#include<iostream>
using namespace std;

//FileLocker 진입점
int main() {
	//로그 검사
	Logger::scan();

	//프로그램 시작
	Logger::log(LOG_MACRO::PROGRAM_START);

	//인터페이스 출력
	Branch* mainMenu = &MainBranch::getMainBranch();
	mainMenu->representComponent();

	//프로그램 정상 종료
	Logger::log(LOG_MACRO::PROGRAM_END_PROPERLY);
	system("pause");

	return 0;
}