#include"Logger.h"

#include<iostream>
using namespace std;
using std::cin;
using std::cout;

#include<fstream>
using std::ifstream;
using std::ofstream;

#include<ctime>
using std::tm;

//로그 파일 경로
string Logger::logFilePath = LOG_FILE_PATH;

/*1. 주어진 데이터를 받아서 정해진 형식대로 텍스트 파일에 기록합니다.*/
void Logger::log(LOG_MACRO logMacro, string description) {
	//텍스트 모드로 파일을 열고 뒤에 추가하는 형식으로 씁니다.
	ofstream logFile(LOG_FILE_PATH, ios::app);
	if (!logFile) {
		throw "Cannot open log file!";
	}


	//현재시간을 문자열로 변환시켜 저장합니다.
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);

	string contents = to_string((newtime.tm_year + 1900)) + "-" + to_string((newtime.tm_mon + 1)) + "-" + to_string((newtime.tm_mday)) + ", "
		+ to_string((newtime.tm_hour)) + ":" + to_string((newtime.tm_min)) + ":" + to_string((newtime.tm_sec));

	contents += " | ";

	switch (logMacro) {
	case LOG_MACRO::ENCRYPTION_START:	contents += "@EncryptionStart | "; break;
	case LOG_MACRO::ENCRYPTION_SUCCESS:	contents += "@EncryptionSuccess | "; break;
	case LOG_MACRO::ENCRYPTION_FAILURE:	contents += "@EncryptionFailure | "; break;
	case LOG_MACRO::DECRYPTION_START:	contents += "@DecryptionStart | "; break;
	case LOG_MACRO::DECRYPTION_SUCCESS:	contents += "@DecryptionSuccess | "; break;
	case LOG_MACRO::DECRYPTION_FAILURE:	contents += "@DecryptionFailure | "; break;
	case LOG_MACRO::PROGRAM_START:		contents += "@START | "; break;
	case LOG_MACRO::PROGRAM_END_PROPERLY:contents += "@END | "; break;
	}

	contents += description + '\n';
	
	//로그 파일은 한 줄에 최대 200줄 까지입니다. 그 이상이 되면 description의 일부가 잘립니다.
	logFile.write(contents.c_str(), contents.size());
}

//전체 로그를 출력해 줍니다.
void Logger::showLog() {
	ifstream logFile(LOG_FILE_PATH, ios::in);
	if (!logFile) {
		//파일이 없는 경우 새 로그 파일을 만듭니다.
		//다른 이유로 열지 못 하는 경우 파일내용이 삭제되는 것을 막기위해서 ios::ate모드를 사용합니다.
		ofstream temp(LOG_FILE_PATH, ios::ate);
		temp.close();

		//파일을 다시 읽습니다.
		logFile.open(LOG_FILE_PATH, ios::in);
		if (!logFile) {
			cout << "로그 파일을 열 수 없습니다!\n";
			return;
		}
	}

	char msg[200];
	while (!logFile.eof()) {
		logFile.getline(msg, 200);
		cout << msg << endl;
	}
}


/*3. 파일로 부터 데이터를 읽어서 이전 실행에서의 문제가 없었는지 확인합니다.*/
#include<stack>
#include<cstring>
void Logger::scan() {

	
	//텍스트 모드로 파일을 읽습니다.
	ifstream logScanner(LOG_FILE_PATH, ios::in);
	if (!logScanner) {
		//파일이 없는 경우 새 로그 파일을 만듭니다.
		//다른 이유로 열지 못 하는 경우 파일내용이 삭제되는 것을 막기위해서 ios::ate모드를 사용합니다.
		ofstream temp(LOG_FILE_PATH, ios::ate);
		temp.close();

		//파일을 다시 읽습니다.
		logScanner.open(LOG_FILE_PATH, ios::in);
		if (!logScanner) {
			cout << "로그 파일을 열 수 없습니다!\n";
			return;
		}
	}

	//읽은 로그들을 기록할 스택
	stack<string> logStack;
	
	//파일에 내용이 없는 경우 바로 끝내기위해 @END로 초기화 합니다.
	char buffer[200];

	//로그 파일에서 모든 기록을 읽어 스택에 넣습니다.
	do {
		logScanner.getline(buffer, 200);
		logStack.push(buffer);
	} while (!logScanner.eof());
	
	//가장 최근 로그부터 하나씩 검사합니다. 만약 처음에 @END를 만났다면 플래그가 false일 것입니다.
	//만약 비정상 종료(메인 메뉴를 통하지 않은 종료)일 경우 처음에 만나는 @START에 의해 검사는 종료됩니다.
	//가장 최근실행 기록 검사가 끝난 후 flag를 검사하여 true인 항목이 있는 경우 
	//시작한 기록은 있는데, 끝난 기록은 없는 것입니다. 즉,  프로그램이 도중에 종료된 것입니다.
	string incompleteEncryption = "";
	string incompleteDecryption = "";
	string log;
	bool encrypt_flag = false;
	bool decrypt_flag = false;
	while (true) {
		if (logStack.size() == 0) { break; }

		log = logStack.top();
		logStack.pop();

		if (log.find("@END") != -1) { break; }
		else if (log.find("@EncryptionStart") != -1) {
			encrypt_flag = (encrypt_flag) ? false : true;
			if (incompleteEncryption == "")
				incompleteEncryption = log;
		}
		else if (log.find("@EncryptionSuccess") != -1) {
			encrypt_flag = (encrypt_flag) ? false : true;
		}
		else if (log.find("@EncryptionFailure") != -1) {
			encrypt_flag = (encrypt_flag) ? false : true;
		}
		else if (log.find("@DecryptionStart") != -1) {
			decrypt_flag = (decrypt_flag) ? false : true;
			if (incompleteDecryption == "")
				incompleteDecryption = log;
		}
		else if (log.find("@DecryptionSuccess") != -1) {
			decrypt_flag = (decrypt_flag) ? false : true;
		}
		else if (log.find("@DecryptionFailure") != -1) {
			decrypt_flag = (decrypt_flag) ? false : true;
		}
		else if (log.find("@START") != -1) { break; }
	}
	
	if (encrypt_flag) {
		cout << incompleteEncryption << endl;
		cout << "암호화 도중에 문제가 생겨 중단되었었습니다." << endl;
	}
	if (decrypt_flag) {
		cout << incompleteDecryption << endl;
		cout << "복호화 도중에 문제가 생겨 중단되었었습니다." << endl;
	}
	//오류가 있었을 시 사용자가 메시지를 읽을 수 있도록 기다려야합니다.
	if (encrypt_flag | decrypt_flag) {
		system("PAUSE");
	}
	
	//스트림을 종료하고, 로그파일에 @END를 넣습니다.
	logScanner.close();
	Logger::log(LOG_MACRO::PROGRAM_END_PROPERLY);
}

/*4. 로그 기록을 초기화합니다.*/
void Logger::reset() {
	ofstream bloomstick(LOG_FILE_PATH, ios::trunc);
	if (!bloomstick) {
		throw "Cannot open log file";
	}
	bloomstick.close();
}