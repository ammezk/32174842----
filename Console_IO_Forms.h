#ifndef CONSOLE_IO_FORMS_H
#define CONSOLE_IO_FORMS_H

/*
콘솔 환경에서의 입력 폼을 제공합니다.
또한 그외 몇 가지 출력 기능을 제공하는 클래스입니다.
*/

#include<iostream>
#include<string>
using namespace std;
using std::cin;
using std::cout;
using std::string;

//aInputForm: 사용자로 부터 하나의 값을 입력 받도록 합니다. 제네릭 함수입니다.
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


//lineInputForm: 사용자로 부터 하나의 라인을 입력 받도록 합니다.
void lineInputForm(/*IN*/ const char* request_to_user, /*IN*/ int max_input_size, /*OUT*/char* sink);
void lineInputForm(/*IN*/ const char* request_to_user, /*OUT*/string& sink);


#include <stdlib.h>
#include <iomanip>
//주어진 폭 만큼 주어진 문자열을 출력해줍니다.
void printLineForm(char endChar, int width, bool dir, string contents);

//콘솔 창의 크기를 주어진 크기로 세팅해줍니다.
void setScreenSize(int width, int height);

//콘솔 창을 깨끗하게 비워줍니다.
void clearAll();

//현재 커서가 있는 라인을 깨끗하게 비워줍니다.
void clearLine();

//주어진 문자를 주어진 개수만큼 출력해줍니다.
void charLine(char symbol, int num);

#endif