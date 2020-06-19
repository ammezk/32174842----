#ifndef LOGGER_H
#define LOGGER_H

#include<string>
using namespace std;
using std::string;

//로그 파일 경로는 프로그램이 존재하는 경로와 같습니다.
constexpr auto LOG_FILE_PATH = ".\\log.txt";


//로그 요청시 외부에서 반드시 제공해야합니다.
enum class LOG_MACRO {
	//암호화(1, 2, 3)
	ENCRYPTION_START = 1,	//시작(1)
	ENCRYPTION_SUCCESS = 2,	//성공(2)
	ENCRYPTION_FAILURE = 3,	//실패(3)

	//복호화(4, 5, 6)
	DECRYPTION_START = 4,	//시작(4)
	DECRYPTION_SUCCESS = 5,	//성공(5)
	DECRYPTION_FAILURE = 6,	//실패(1)

	//프로그램(0, -1)
	PROGRAM_START = 0,			//시작(0)
	PROGRAM_END_PROPERLY = -1,	//정상종료(-1)
};


/*
프로그램의 동작에 대한 전반적인 정보를 텍스트파일에 저장합니다.
외부에서 요청이 들어오면, 로그 형식에 맞게 기록하는데,
프로그램의 시작과 끝, 동작의 시작 그리고 실패 또는 성공 여부를 기록합니다.

또한 프로그램이 처음 시작될 때 호출되어 이전 실행에서의 문제점이 있었는지 검토합니다.
만약 문제가 있었다면 사용자에게 이를 알리고, 다음 실행에서 부터는 이에 대해
알리지 않습니다.

로그 형식은 아래와 같습니다.

	System time | LogMacro | Description \n

로그 클래스는 객체를 만들지 못하며, 오직 정적 메소드를 통해서 기능을 제공합니다.
*/

class Logger {
private:
	static string logFilePath;
	Logger() {}
public:
	/*1. 주어진 데이터를 받아서 정해진 형식대로 텍스트 파일에 기록합니다.*/
	static void log(LOG_MACRO logMacro, string description = "NONE");

	/*2. 로그 파일을 조회합니다.*/
	static void showLog();

	/*3. 파일로 부터 데이터를 읽어서 이전 실행에서의 문제가 없었는지 확인합니다.*/
	static void scan();

	/*4. 로그 기록을 초기화합니다.*/
	static void reset();
};
#endif