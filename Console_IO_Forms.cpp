#include"Console_IO_Forms.h"

//lineInputForm: 사용자로 부터 하나의 라인을 입력 받도록 합니다.
void lineInputForm(/*IN*/ const char* request_to_user, /*IN*/ int max_input_size, /*OUT*/char* sink) {
	cout << request_to_user;
	cin.getline(sink, max_input_size);
	if (cin.good()) {
		return;
	}
	else {
		cin.clear();
		throw "Standard input stream error occured";
	}
}
void lineInputForm(/*IN*/ const char* request_to_user, /*OUT*/string& sink) {
	cout << request_to_user;
	getline(cin, sink);
	if (cin.good()) {
		return;
	}
	else {
		cin.clear();
		throw "Standard input stream error occured";
	}
}

//주어진 폭 만큼 주어진 문자열을 출력해줍니다.
void printLineForm(char endChar, int width, bool is_left, string contents) {
	cout << endChar;
	if (is_left == true) 
		cout << setw(width-2) << left << contents;
	else
		cout << setw(width - 2) << right << contents;
	cout << endChar << endl;
}

//콘솔 창의 크기를 주어진 크기로 세팅해줍니다.
void setScreenSize(int width, int height) {
	int margin = 1;
	string setcmd = "mode con lines=";
	setcmd += std::to_string(height) + " cols=" + std::to_string(width);
	system(setcmd.c_str());
}

//콘솔 창을 깨끗하게 비워줍니다.
void clearAll() {
	system("cls");
}

//현재 커서가 있는 라인을 깨끗하게 비워줍니다.
void clearLine() {
	cout << "\33[2K\r";
}

//주어진 문자를 주어진 개수만큼 출력
void charLine(char symbol, int num) {
	if (num > 300)
		return;
	else {
		char buffer[301];
		for (int i = 0; i < num; i++) {
			buffer[i] = symbol;
		}
		buffer[num] = '\0';
		cout << buffer;
	}
}