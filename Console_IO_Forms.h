#ifndef CONSOLE_IO_FORMS_H
#define CONSOLE_IO_FORMS_H

/*
�ܼ� ȯ�濡���� �Է� ���� �����մϴ�.
���� �׿� �� ���� ��� ����� �����ϴ� Ŭ�����Դϴ�.
*/

#include<iostream>
#include<string>
using namespace std;
using std::cin;
using std::cout;
using std::string;

//aInputForm: ����ڷ� ���� �ϳ��� ���� �Է� �޵��� �մϴ�. ���׸� �Լ��Դϴ�.
template<typename T>
void aInputForm(/*IN*/ const char* request_to_user, /*OUT*/T & sink);

template<typename T>
void aInputForm(/*IN*/ const char* request_to_user, /*OUT*/T & sink){
	cout << request_to_user;
	cin >> sink;

	if (cin.good()) {
		cin.ignore(10, '\n');
		return;
	}
	else {
		cin.clear();
		cin.ignore(300, '\n');
		throw "Standard input stream error";
	}
}


//lineInputForm: ����ڷ� ���� �ϳ��� ������ �Է� �޵��� �մϴ�.
void lineInputForm(/*IN*/ const char* request_to_user, /*IN*/ int max_input_size, /*OUT*/char* sink);
void lineInputForm(/*IN*/ const char* request_to_user, /*OUT*/string& sink);


#include <stdlib.h>
#include <iomanip>
//�־��� �� ��ŭ �־��� ���ڿ��� ������ݴϴ�.
void printLineForm(char endChar, int width, bool dir, string contents);

//�ܼ� â�� ũ�⸦ �־��� ũ��� �������ݴϴ�.
void setScreenSize(int width, int height);

//�ܼ� â�� �����ϰ� ����ݴϴ�.
void clearAll();

//���� Ŀ���� �ִ� ������ �����ϰ� ����ݴϴ�.
void clearLine();

//�־��� ���ڸ� �־��� ������ŭ ������ݴϴ�.
void charLine(char symbol, int num);

#endif