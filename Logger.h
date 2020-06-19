#ifndef LOGGER_H
#define LOGGER_H

#include<string>
using namespace std;
using std::string;

//�α� ���� ��δ� ���α׷��� �����ϴ� ��ο� �����ϴ�.
constexpr auto LOG_FILE_PATH = ".\\log.txt";


//�α� ��û�� �ܺο��� �ݵ�� �����ؾ��մϴ�.
enum class LOG_MACRO {
	//��ȣȭ(1, 2, 3)
	ENCRYPTION_START = 1,	//����(1)
	ENCRYPTION_SUCCESS = 2,	//����(2)
	ENCRYPTION_FAILURE = 3,	//����(3)

	//��ȣȭ(4, 5, 6)
	DECRYPTION_START = 4,	//����(4)
	DECRYPTION_SUCCESS = 5,	//����(5)
	DECRYPTION_FAILURE = 6,	//����(1)

	//���α׷�(0, -1)
	PROGRAM_START = 0,			//����(0)
	PROGRAM_END_PROPERLY = -1,	//��������(-1)
};


/*
���α׷��� ���ۿ� ���� �������� ������ �ؽ�Ʈ���Ͽ� �����մϴ�.
�ܺο��� ��û�� ������, �α� ���Ŀ� �°� ����ϴµ�,
���α׷��� ���۰� ��, ������ ���� �׸��� ���� �Ǵ� ���� ���θ� ����մϴ�.

���� ���α׷��� ó�� ���۵� �� ȣ��Ǿ� ���� ���࿡���� �������� �־����� �����մϴ�.
���� ������ �־��ٸ� ����ڿ��� �̸� �˸���, ���� ���࿡�� ���ʹ� �̿� ����
�˸��� �ʽ��ϴ�.

�α� ������ �Ʒ��� �����ϴ�.

	System time | LogMacro | Description \n

�α� Ŭ������ ��ü�� ������ ���ϸ�, ���� ���� �޼ҵ带 ���ؼ� ����� �����մϴ�.
*/

class Logger {
private:
	static string logFilePath;
	Logger() {}
public:
	/*1. �־��� �����͸� �޾Ƽ� ������ ���Ĵ�� �ؽ�Ʈ ���Ͽ� ����մϴ�.*/
	static void log(LOG_MACRO logMacro, string description = "NONE");

	/*2. �α� ������ ��ȸ�մϴ�.*/
	static void showLog();

	/*3. ���Ϸ� ���� �����͸� �о ���� ���࿡���� ������ �������� Ȯ���մϴ�.*/
	static void scan();

	/*4. �α� ����� �ʱ�ȭ�մϴ�.*/
	static void reset();
};
#endif