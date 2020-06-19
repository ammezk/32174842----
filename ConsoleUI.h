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
추상 사용자 인터페이스 요소로 다형성을 제공하기 위해 만들어진 추상클래스입니다.
------------------------------------------------------------------------
1.	추상 클래스임을 명시해주기위한 비어있는 순수 가상함수를 만듭니다.
	이 순수 가상 함수는 최 하위의 구상 클래스를 만날때 까지 구현해서는
	안 됩니다. final클래스에서 해당 함수를 비어있는 형태로 구현합니다.

2.	순수 가상함수 representComponent를 선언합니다. 이 요소는 하위 클래스인
	Branch, Page클래스에서 재정의됩니다.

3.	description 필드를 가집니다. 이 필드는 최 하위 구상 Brach나 구상 Page 클래스
	객체가 생성될 때 결정됩니다.
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
요약:
ConsoleUI_Component- Branch(분기)는
여러 선택지를 화면에 출력하고 사용자가 선택하게끔
제공하는 유형의 콘솔 유저인터페이스 구성요소입니다.

이 클래스에서는 Branch유형의 요소를 어떻게 화면에 출력할 것이고
사용자로부터 선택지를 입력받을 것인지에 대한 내용이 정의됩니다.

사용자에게 제공될 구성요소들이 구체적으로 무엇인지는
Branch를 상속받는 구상 분기 클래스에서 정의하게 될 것 입니다.
------------------------------------------------------------------

1) 인덱싱이 가능한 Component컨테이너를 포함해야 합니다.
	: 이때 어떤 Component들이 포함될 것인가는 하위 구상 클래스에서
	  정하게됩니다.(팩토리 개념)

2) @Override representComponent
	:구상 Branch로 부터 결정된 Component컨테이너를 바탕으로
	 사용자에게 선택지를 제시해야합니다.

3) 제공되는 Component들은 또 다른 분기이거나 Page일 수 있습니다.
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
요약:
ConsoleUI_Component- Page는 분기로 부터 사용자가 선택한 구체적인
기능을 제공하기 위해 관련 정보를 출력하거나 입력받는 일련의 단계입니다.

Page클래스에서는 구체적인 출력내용 등은 정의하지 않고 구상 Page클래스
에서 정한 바에 따라 페이지의 각 단계를 사용자에게 제시할 뿐입니다.

각 단계(step)에 해당하는 함수들은 구상 Page클래스에 구체적으로 정의되어야 합니다.

하나의 단계는 사용자의 선택이나, 특정 상황에 따라 계속 진행하거나,
현재 단계를 다시 수행하거나, 이전 단계로 돌아갈 수 있습니다.
------------------------------------------------------------------

1) 순서가 존재하는 함수 포인터 컨테이너를 포함해야 합니다.
	: 어떤 함수가 어떤 순서로 포함될 것인가는 하위 구상 Page클래스
	  에서 정의하게 됩니다.(팩토리 개념)

2) @Override representComponent
	:일련의 순서에 따라 각 단계를 제시합니다. 이때 진행 방향은 사용자의
	 선택이나, 상황에 따라 결정됩니다.

3) enum class DIRECTION
	: 이 열거형은 진행 방향을 나타내며 Enum class로서 Page 내부에 정의되어
	  있습니다. 각 단계들은 DIRECTION값을 반환하여 Page클래스에게 진행
	  방향이 어떻게 될 것인지 알립니다.

4) 가장 처음 단계에서 이전으로 돌아가게 된다면, 해당 Page를 호출 한 가장 최근
	의 분기로 이동하게 될 것입니다.
*/
#include<list>
class Page : public Component {
protected:
	//진향 방향에 대한 열거형
	enum class DIRECTION { UNDO = -1, RE = 0, NEXT = 1 };
	//stepContainer의 각 요소는 함수입니다.
	list<DIRECTION(*)()>* stepContainer;
	//사용자로 부터 진행 방향을 묻는 함수
	static DIRECTION whichDir();
public:
	Page();
	void representComponent();
	virtual ~Page();
};
#endif