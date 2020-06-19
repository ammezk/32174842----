#include"ConsoleUI.h"
#include"Console_IO_Forms.h"

/*===============Branch 클래스를 정의하는 부분입니다.===============*/
Branch::Branch() : Component() {
	componentContainer = new vector<Component*>();
}

//componentContainer를 바탕으로 사용자에게 선택 목록을 제시합니다.
void Branch::representComponent() {
	//Branch의 창 크기를 설정합니다.
	const int width = 110;
	const int height = 40;
	setScreenSize(width, height);

	while(true) {
		clearAll();

		//선택된 분기에 대한 description을 출력합니다.
		cout << "|"; charLine('=', width - 2); cout << "|";
		printLineForm('|', width, true, description);
		cout << "|"; charLine('-', width - 2); cout << "|";

		//사용자에게 선택지를 제시합니다.
		for (int i = 0; i < componentContainer->size(); i++) {
			printLineForm('|', width, true,
				std::to_string(i+1) + ". " + (*componentContainer)[i]->getDescription());
		}
		printLineForm('|', width, true,
			std::to_string(componentContainer->size() + 1) + ". " + "return");
		cout << "|"; charLine('=', width - 2); cout << "|";

		//사용자 입력 폼
		int user_choice = -1;
		while (true) {
			try {
				aInputForm<int>("Choice number you want >> ", user_choice);
				if (user_choice < 1 || user_choice > componentContainer->size() + 1) {
					cout << "\x1b[A"; clearLine();
				}
				else {
					break;
				}
			}
			catch (const char* msg) {
				cout << "\x1b[A"; clearLine();
			}
		}
		
		//사용자가 return을 선택한 경우
		if (user_choice == componentContainer->size() + 1) {
			return;
		}
		//사용자가 다른 항목을 선택한 경우
		else {
			(*componentContainer)[user_choice - 1]->representComponent();
		}
	}
}
Branch::~Branch() {
	delete componentContainer;
}


/*===============Page 클래스를 정의하는 부분입니다.===============*/
Page::Page() : Component() {
	stepContainer = new list<DIRECTION (*)()>();
}

//stepContainer를 바탕으로 사용자가 단계별로 수행할 수 있도록 제시 합니다.
void Page::representComponent() {
	//Page의 창 크기를 설정합니다.
	const int width = 110;
	const int height = 40;
	setScreenSize(width, height);

	//만약 컨테이너가 비어있다면 해당 페이지를 종료하고, 아니라면 화면을 비웁니다.
	if (stepContainer->empty()) {
		return;
	}

	list<DIRECTION(*)()>::iterator it;
	it = stepContainer->begin();
	int stepNum=1;

	while (true) {
		//창을 비웁니다.
		clearAll();

		//사용자에게 Page의 현재 단계를 보입니다. 이는 해당 단계에 해당하는 함수에서 구현해야 합니다.
		charLine('*', width);
		printLineForm('*', width, true, description + "#" + to_string(stepNum));
		charLine('*', width);
		DIRECTION dir;
		dir = (*it)();

		//step의 반환 결과에 따라서 진행 방향을 결정합니다.
		switch (dir) {
		case DIRECTION::NEXT:
			it++, stepNum++;
			if (it == stepContainer->end()) return;		//마지막의 다음은 페이지 종료
			else break;
		case DIRECTION::RE:
			break;
		case DIRECTION::UNDO:
			if (it == stepContainer->begin()) return;	//처음의 이전은 페이지 종료
			else it--, stepNum--;
			break;
		}
	}
}

Page::DIRECTION Page::whichDir() {
	//이전? 다시? 다음?
	int user_choice;
	while (true) {
		try {
			aInputForm<int>("UNDO(-1), RE(0), NEXT(1) >> ", user_choice);
			if (user_choice == (int)DIRECTION::UNDO) return DIRECTION::UNDO;
			else if (user_choice == (int)DIRECTION::RE) return DIRECTION::RE;
			else if (user_choice == (int)DIRECTION::NEXT) return DIRECTION::NEXT;
			else {
				cout << "\x1b[A"; clearLine();
			}
		}
		catch (const char* msg) {
			cout << "\x1b[A"; clearLine();
		}
	}
}
Page::~Page() {
	delete stepContainer;
}