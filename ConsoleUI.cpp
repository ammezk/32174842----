#include"ConsoleUI.h"
#include"Console_IO_Forms.h"

/*===============Branch Ŭ������ �����ϴ� �κ��Դϴ�.===============*/
Branch::Branch() : Component() {
	componentContainer = new vector<Component*>();
}

//componentContainer�� �������� ����ڿ��� ���� ����� �����մϴ�.
void Branch::representComponent() {
	//Branch�� â ũ�⸦ �����մϴ�.
	const int width = 110;
	const int height = 40;
	setScreenSize(width, height);

	while(true) {
		clearAll();

		//���õ� �б⿡ ���� description�� ����մϴ�.
		cout << "|"; charLine('=', width - 2); cout << "|";
		printLineForm('|', width, true, description);
		cout << "|"; charLine('-', width - 2); cout << "|";

		//����ڿ��� �������� �����մϴ�.
		for (int i = 0; i < componentContainer->size(); i++) {
			printLineForm('|', width, true,
				std::to_string(i+1) + ". " + (*componentContainer)[i]->getDescription());
		}
		printLineForm('|', width, true,
			std::to_string(componentContainer->size() + 1) + ". " + "return");
		cout << "|"; charLine('=', width - 2); cout << "|";

		//����� �Է� ��
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
		
		//����ڰ� return�� ������ ���
		if (user_choice == componentContainer->size() + 1) {
			return;
		}
		//����ڰ� �ٸ� �׸��� ������ ���
		else {
			(*componentContainer)[user_choice - 1]->representComponent();
		}
	}
}
Branch::~Branch() {
	delete componentContainer;
}


/*===============Page Ŭ������ �����ϴ� �κ��Դϴ�.===============*/
Page::Page() : Component() {
	stepContainer = new list<DIRECTION (*)()>();
}

//stepContainer�� �������� ����ڰ� �ܰ躰�� ������ �� �ֵ��� ���� �մϴ�.
void Page::representComponent() {
	//Page�� â ũ�⸦ �����մϴ�.
	const int width = 110;
	const int height = 40;
	setScreenSize(width, height);

	//���� �����̳ʰ� ����ִٸ� �ش� �������� �����ϰ�, �ƴ϶�� ȭ���� ���ϴ�.
	if (stepContainer->empty()) {
		return;
	}

	list<DIRECTION(*)()>::iterator it;
	it = stepContainer->begin();
	int stepNum=1;

	while (true) {
		//â�� ���ϴ�.
		clearAll();

		//����ڿ��� Page�� ���� �ܰ踦 ���Դϴ�. �̴� �ش� �ܰ迡 �ش��ϴ� �Լ����� �����ؾ� �մϴ�.
		charLine('*', width);
		printLineForm('*', width, true, description + "#" + to_string(stepNum));
		charLine('*', width);
		DIRECTION dir;
		dir = (*it)();

		//step�� ��ȯ ����� ���� ���� ������ �����մϴ�.
		switch (dir) {
		case DIRECTION::NEXT:
			it++, stepNum++;
			if (it == stepContainer->end()) return;		//�������� ������ ������ ����
			else break;
		case DIRECTION::RE:
			break;
		case DIRECTION::UNDO:
			if (it == stepContainer->begin()) return;	//ó���� ������ ������ ����
			else it--, stepNum--;
			break;
		}
	}
}

Page::DIRECTION Page::whichDir() {
	//����? �ٽ�? ����?
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