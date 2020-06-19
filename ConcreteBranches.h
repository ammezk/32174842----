#ifndef CONCRETEBRANCHES_H
#define CONCRETEBRANCHES_H

#include"ConsoleUI.h"
#include"ConcretePages.h"

/*
구상 Component(구상 Branch 또는 구상 Page)들을 만들어서 componentContainer 벡터에
할당하는 구상 Branch클래스를 정의합니다.

모든 UI 요소들은 유일하게 존재해야합니다.(Concrete Branches, Concrete Pages)
따라서 싱글턴 패턴을 이용하여 유일하게 존재할 수 있도록 구현했습니다..

구성 분기 요소에는 현재 MainBranch와 LogBranch가 있습니다.
새로운 구상 분기 클래스를 정의함으로써 콘솔 유저 인터페이스를 용이하게 확장할 수 있습니다.
*/

/*
MainBranch
componentContainer에
1. EncryptionPage
2. DecryptionPage
3. LogPage
를 넣습니다.
*/
class MainBranch : public Branch {
private:
	//외부에서 맘대로 MainBranch 객체를 생성하지 못하게 만들기 위해서
	//모든 생성자는 private입니다.
	MainBranch();
	MainBranch(MainBranch&) : Branch() {}
	static MainBranch uniqueMainBranch;
protected:
	void is_final() {/*이 클래스는 구상 클래스로 더 이상 확장하지 않습니다.*/}
public:
	//외부에 자기자신에 대한 참조를 제공합니다.
	static MainBranch& getMainBranch() { return uniqueMainBranch; }
	virtual ~MainBranch() {}
};


/*
LogBranch
componentContainer에
1. ShowLogPage
2. DeleteLogPage
를 넣습니다.
*/
class LogBranch : public Branch {
private:
	//외부에서 맘대로 LogPage객체를 생성하지 못하게 만들기 위해서
	//모든 생성자는 private입니다.
	LogBranch();
	LogBranch(LogBranch&) : Branch() {}
	static LogBranch uniqueLogBranch;
protected:
	void is_final() {/*이 클래스는 구상 클래스로 더 이상 확장하지 않습니다.*/ }
public:
	//외부에 자기자신에 대한 참조를 제공합니다.
	static LogBranch& getLogBranch() { return uniqueLogBranch; }
	virtual ~LogBranch() {}
};
#endif