using namespace std;
#include <list> 
#include <iostream>
#include <typeinfo>

class Subject;

class Observer
{
public:
	virtual Update(Subject* subject) = 0;
};

class Subject
{
public:
	
	Attach(Observer *observer) {
		m_observers.push_front(observer);
	}
	
	Dettach(Observer *observer) {
		m_observers.remove(observer);
	}

	Notify() {
		list<Observer*>::iterator it;
		for (it = m_observers.begin() ; it != m_observers.end(); ++it) {
					(*it)->Update(this);
		}
	}

private:
	list<Observer*> m_observers;
};

class AnotherSubject : public Subject 
{
public:
	
};

class CoilManager : public Subject
{
public:
	CoilManager() : m_enabled(false) {};
	~CoilManager() {};
	SetCoilEnabled(bool enable) {
		m_enabled = enable;
		Notify();
	}

	bool GetCoilState() {
		return m_enabled;
	}

private:
	bool m_enabled;	
};

class LogManager : public Observer
{
public:
	LogManager(Subject *subject) {
		subject->Attach(this);
	}
	~LogManager() {};

	Update(Subject* subject) {
		cout << typeid(*subject).name() << endl;
	}

	Update(CoilManager* coilManager) {
		cout << "Coil State: "<< coilManager->GetCoilState() << endl;
	}	
};

int main(int argc, char const *argv[])
{
	cout<< "Observer pattern example:"<<endl;
	AnotherSubject anotherSubject;
	CoilManager coilManager;
	LogManager logManager(&coilManager); // auto attach to coilManager
	anotherSubject.Attach(&logManager); // manually attach to anotherSubject

	coilManager.SetCoilEnabled(true); // automatically Notify Observers when state changes
	anotherSubject.Notify(); // manually notify observers

	return 0;
}