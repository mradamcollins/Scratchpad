using namespace std;
#include <iostream>
#include <list>

class Command
{
public:
	virtual void Execute() = 0;
	virtual void Revoke() = 0;
};

class Invoker
{
public:
	void Invoke(Command& cmd) { 
		cmd.Execute();
		
		m_undoCommands.push_back(&cmd);
		m_redoCommands.clear();
	};
	void Undo() {
		if (m_undoCommands.empty()) {
			cout << "Nothing to Undo!" << endl;
			return;
		}

		Command* cmd = m_undoCommands.back();
		m_undoCommands.pop_back();
		cmd->Revoke();
		m_redoCommands.push_back(cmd);
	};
	void Redo()	{
		if (m_redoCommands.empty()) {
			cout << "Nothing to Redo!" << endl;
			return;
		}

		Command* cmd = m_redoCommands.back();
		m_redoCommands.pop_back();
		cmd->Execute();
		m_undoCommands.push_back(cmd);
	};
private:
	
	list<Command*> m_undoCommands;
	list<Command*> m_redoCommands;
};

class Receiver
{
public:
	void DoSomething() { cout << "Doing something!" << endl; }
	void UndoDoSomething() { cout << "UnDoing something!" << endl; }
	void DoSomethingElse() { cout << "Doing something else!" << endl; }
	void UndoDoSomethingElse() { cout << "UnDoing something else!" << endl; }
};

class DoSomethingCommand : public Command
{
public:
	DoSomethingCommand(Receiver& receiver) : m_receiver(receiver) {};
	virtual void Execute() { m_receiver.DoSomething(); }
	virtual void Revoke() { m_receiver.UndoDoSomething(); }
private:
	Receiver& m_receiver;
};

class DoSomethingElseCommand : public Command
{
public:
	DoSomethingElseCommand(Receiver& receiver) : m_receiver(receiver) {};
	virtual void Execute() { m_receiver.DoSomethingElse(); }
	virtual void Revoke() { m_receiver.UndoDoSomethingElse(); }
private:
	Receiver& m_receiver;
};

int main(int argc, char const *argv[])
{
	Invoker my_invoker;
	Receiver my_receiver;
	DoSomethingCommand doSomethingCmd(my_receiver);
	DoSomethingElseCommand doSomethingElseCmd(my_receiver);

	my_invoker.Invoke(doSomethingCmd);
	my_invoker.Invoke(doSomethingElseCmd);
	my_invoker.Invoke(doSomethingCmd);
	my_invoker.Undo();
	my_invoker.Undo();
	my_invoker.Invoke(doSomethingCmd);
	my_invoker.Redo();
	my_invoker.Undo();
	return 0;
}