#ifndef REPORT_H
#define REPORT_H

#include<string>
using namespace std;

/*
이 구조체는 암복호화기 모듈에서 사용되는 메시지 구조체입니다.
*/
struct Report {
	bool is_success;
	string msg;

	Report(bool is_success = false, string msg = "NONE");
	Report(Report& rpt);
};

#endif