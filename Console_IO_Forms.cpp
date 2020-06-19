#include"Console_IO_Forms.h"

//lineInputForm: ����ڷ� ���� �ϳ��� ������ �Է� �޵��� �մϴ�.
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

//�־��� �� ��ŭ �־��� ���ڿ��� ������ݴϴ�.
void printLineForm(char endChar, int width, bool is_left, string contents) {
	cout << endChar;
	if (is_left == true) 
		cout << setw(width-2) << left << contents;
	else
		cout << setw(width - 2) << right << contents;
	cout << endChar << endl;
}

//�ܼ� â�� ũ�⸦ �־��� ũ��� �������ݴϴ�.
void setScreenSize(int width, int height) {
	int margin = 1;
	string setcmd = "mode con lines=";
	setcmd += std::to_string(height) + " cols=" + std::to_string(width);
	system(setcmd.c_str());
}

//�ܼ� â�� �����ϰ� ����ݴϴ�.
void clearAll() {
	system("cls");
}

//���� Ŀ���� �ִ� ������ �����ϰ� ����ݴϴ�.
void clearLine() {
	cout << "\33[2K\r";
}

//�־��� ���ڸ� �־��� ������ŭ ���
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