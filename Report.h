#ifndef REPORT_H
#define REPORT_H

#include<string>
using namespace std;

/*
�� ����ü�� �Ϻ�ȣȭ�� ��⿡�� ���Ǵ� �޽��� ����ü�Դϴ�.
*/
struct Report {
	bool is_success;
	string msg;

	Report(bool is_success = false, string msg = "NONE");
	Report(Report& rpt);
};

#endif