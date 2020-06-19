#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include<iostream>
#include<string>
using namespace std;
using std::cout;
using std::cin;
using std::string;

/*
ConsoleUI_Component(typedef : Component)
�߻� ����� �������̽� ��ҷ� �������� �����ϱ� ���� ������� �߻�Ŭ�����Դϴ�.
------------------------------------------------------------------------
1.	�߻� Ŭ�������� ������ֱ����� ����ִ� ���� �����Լ��� ����ϴ�.
	�� ���� ���� �Լ��� �� ������ ���� Ŭ������ ������ ���� �����ؼ���
	�� �˴ϴ�. finalŬ�������� �ش� �Լ��� ����ִ� ���·� �����մϴ�.

2.	���� �����Լ� representComponent�� �����մϴ�. �� ��Ҵ� ���� Ŭ������
	Branch, PageŬ�������� �����ǵ˴ϴ�.

3.	description �ʵ带 �����ϴ�. �� �ʵ�� �� ���� ���� Brach�� ���� Page Ŭ����
	��ü�� ������ �� �����˴ϴ�.
*/

typedef class ConsoleUI_Component {
protected:
	virtual void is_final() = 0;
	string description;
public:	
	ConsoleUI_Component() {}
	string getDescription() { return description; }
	virtual void representComponent() = 0;
	virtual ~ConsoleUI_Component() {}
}Component;


/*
class Branch
���:
ConsoleUI_Component- Branch(�б�)��
���� �������� ȭ�鿡 ����ϰ� ����ڰ� �����ϰԲ�
�����ϴ� ������ �ܼ� �����������̽� ��������Դϴ�.

�� Ŭ���������� Branch������ ��Ҹ� ��� ȭ�鿡 ����� ���̰�
����ڷκ��� �������� �Է¹��� �������� ���� ������ ���ǵ˴ϴ�.

����ڿ��� ������ ������ҵ��� ��ü������ ����������
Branch�� ��ӹ޴� ���� �б� Ŭ�������� �����ϰ� �� �� �Դϴ�.
------------------------------------------------------------------

1) �ε����� ������ Component�����̳ʸ� �����ؾ� �մϴ�.
	: �̶� � Component���� ���Ե� ���ΰ��� ���� ���� Ŭ��������
	  ���ϰԵ˴ϴ�.(���丮 ����)

2) @Override representComponent
	:���� Branch�� ���� ������ Component�����̳ʸ� ��������
	 ����ڿ��� �������� �����ؾ��մϴ�.

3) �����Ǵ� Component���� �� �ٸ� �б��̰ų� Page�� �� �ֽ��ϴ�.
*/
#include<vector>
class Branch : public Component {
protected:
	virtual void is_final() = 0;
	vector<Component*>* componentContainer;
public:
	Branch();
	void representComponent();
	virtual ~Branch();
};


/*
���:
ConsoleUI_Component- Page�� �б�� ���� ����ڰ� ������ ��ü����
����� �����ϱ� ���� ���� ������ ����ϰų� �Է¹޴� �Ϸ��� �ܰ��Դϴ�.

PageŬ���������� ��ü���� ��³��� ���� �������� �ʰ� ���� PageŬ����
���� ���� �ٿ� ���� �������� �� �ܰ踦 ����ڿ��� ������ ���Դϴ�.

�� �ܰ�(step)�� �ش��ϴ� �Լ����� ���� PageŬ������ ��ü������ ���ǵǾ�� �մϴ�.

�ϳ��� �ܰ�� ������� �����̳�, Ư�� ��Ȳ�� ���� ��� �����ϰų�,
���� �ܰ踦 �ٽ� �����ϰų�, ���� �ܰ�� ���ư� �� �ֽ��ϴ�.
------------------------------------------------------------------

1) ������ �����ϴ� �Լ� ������ �����̳ʸ� �����ؾ� �մϴ�.
	: � �Լ��� � ������ ���Ե� ���ΰ��� ���� ���� PageŬ����
	  ���� �����ϰ� �˴ϴ�.(���丮 ����)

2) @Override representComponent
	:�Ϸ��� ������ ���� �� �ܰ踦 �����մϴ�. �̶� ���� ������ �������
	 �����̳�, ��Ȳ�� ���� �����˴ϴ�.

3) enum class DIRECTION
	: �� �������� ���� ������ ��Ÿ���� Enum class�μ� Page ���ο� ���ǵǾ�
	  �ֽ��ϴ�. �� �ܰ���� DIRECTION���� ��ȯ�Ͽ� PageŬ�������� ����
	  ������ ��� �� ������ �˸��ϴ�.

4) ���� ó�� �ܰ迡�� �������� ���ư��� �ȴٸ�, �ش� Page�� ȣ�� �� ���� �ֱ�
	�� �б�� �̵��ϰ� �� ���Դϴ�.
*/
#include<list>
class Page : public Component {
protected:
	//���� ���⿡ ���� ������
	enum class DIRECTION { UNDO = -1, RE = 0, NEXT = 1 };
	//stepContainer�� �� ��Ҵ� �Լ��Դϴ�.
	list<DIRECTION(*)()>* stepContainer;
	//����ڷ� ���� ���� ������ ���� �Լ�
	static DIRECTION whichDir();
public:
	Page();
	void representComponent();
	virtual ~Page();
};
#endif