#include"Report.h"

Report::Report(bool is_success, string msg) {
	this->is_success = is_success;
	this->msg = msg;
}
Report::Report(Report& rpt) {
	this->is_success = rpt.is_success;
	this->msg = rpt.msg;
}