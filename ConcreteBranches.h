#ifndef CONCRETEBRANCHES_H
#define CONCRETEBRANCHES_H

#include"ConsoleUI.h"
#include"ConcretePages.h"

/*
���� Component(���� Branch �Ǵ� ���� Page)���� ���� componentContainer ���Ϳ�
�Ҵ��ϴ� ���� BranchŬ������ �����մϴ�.

��� UI ��ҵ��� �����ϰ� �����ؾ��մϴ�.(Concrete Branches, Concrete Pages)
���� �̱��� ������ �̿��Ͽ� �����ϰ� ������ �� �ֵ��� �����߽��ϴ�..

���� �б� ��ҿ��� ���� MainBranch�� LogBranch�� �ֽ��ϴ�.
���ο� ���� �б� Ŭ������ ���������ν� �ܼ� ���� �������̽��� �����ϰ� Ȯ���� �� �ֽ��ϴ�.
*/

/*
MainBranch
componentContainer��
1. EncryptionPage
2. DecryptionPage
3. LogPage
�� �ֽ��ϴ�.
*/
class MainBranch : public Branch {
private:
	//�ܺο��� ����� MainBranch ��ü�� �������� ���ϰ� ����� ���ؼ�
	//��� �����ڴ� private�Դϴ�.
	MainBranch();
	MainBranch(MainBranch&) : Branch() {}
	static MainBranch uniqueMainBranch;
protected:
	void is_final() {/*�� Ŭ������ ���� Ŭ������ �� �̻� Ȯ������ �ʽ��ϴ�.*/}
public:
	//�ܺο� �ڱ��ڽſ� ���� ������ �����մϴ�.
	static MainBranch& getMainBranch() { return uniqueMainBranch; }
	virtual ~MainBranch() {}
};


/*
LogBranch
componentContainer��
1. ShowLogPage
2. DeleteLogPage
�� �ֽ��ϴ�.
*/
class LogBranch : public Branch {
private:
	//�ܺο��� ����� LogPage��ü�� �������� ���ϰ� ����� ���ؼ�
	//��� �����ڴ� private�Դϴ�.
	LogBranch();
	LogBranch(LogBranch&) : Branch() {}
	static LogBranch uniqueLogBranch;
protected:
	void is_final() {/*�� Ŭ������ ���� Ŭ������ �� �̻� Ȯ������ �ʽ��ϴ�.*/ }
public:
	//�ܺο� �ڱ��ڽſ� ���� ������ �����մϴ�.
	static LogBranch& getLogBranch() { return uniqueLogBranch; }
	virtual ~LogBranch() {}
};
#endif