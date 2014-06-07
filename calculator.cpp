using namespace std;
#include <memory>
#include <iostream>
#include <map>
#include <termios.h>

/** COMMANDS **/
// Abstract interface 
class Command
{
public:
	virtual void Execute() = 0;		// main interface to allow execution of commands
	virtual void Undo() = 0;		// provides a way to support reversible history
};

// concrete implementaion
class AddCommand : public Command
{
public:
	AddCommand();
	~AddCommand();
	
};

class DisplayCommand : public Command
{

};


/** COMPONENTS **/
// Is the command invoker - it doesn't know how to fullfil cmds, only that it can execute them.
class Button
{
public:
	Button(unique_ptr<Command> &&cmd) : mp_cmd(move(cmd)) {};
	
	void Click() {
		mp_cmd->Execute();
	}
private:
	unique_ptr<Command> mp_cmd;
};

/** MAIN CLASS **/
/* Calculator is the command client - it knows how to fullfil commands i.e. 
   it knows the concrete commands and associated recievers it wants to use. 
   (it could also set itself to be the receiver - or have no receiver if the command is self contained)
   it also needs to bind commands to invokers ( who)
*/
class Calculator
{
public:
	Calculator() {
		cout << "Creating a calculator" << endl;		
	}

	void ClickButton(const char id) {
		auto button_it = m_buttons.find(id);
		if ( button_it == m_buttons.end()) {
			cout << "Button " << id << " wasn't found on the calculator!" << endl;
		} else {
			button_it->second.Click();
		}
	}

private:
	void AddButton(char id, Command cmd)
	map<char, Button> m_buttons;
};

/** APPLICATION **/
int main(int argc, char const *argv[])
{
	
	termios before, after;
	tcgetattr (0, &before);  			// fill 'before' with current termios values
	after = before;                     // make a copy to be modified
	after.c_lflag &= (~ICANON);         // Disable canonical mode, including line buffering
	after.c_lflag &= (~ECHO);           // Don't echo characters on the screen (optional)
	tcsetattr (0, TCSANOW, &after); 	// Set the modified flags

	Calculator calc;
	char id;

	cin.get(id);
	while (cin.good())
	{
		calc.ClickButton(id);		
		cin.get(id);
	}

	// restore termios state
	tcsetattr (0, TCSANOW, &before);

	return 0;
}