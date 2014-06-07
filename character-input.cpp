#include <iostream>
#include <termios.h>
using namespace std;

int main(int argc, char const *argv[])
{
	termios before, after;
	tcgetattr (0, &before);  // fill 'before' with current termios values
	after = before;                     // make a copy to be modified
	after.c_lflag &= (~ICANON);         // Disable canonical mode, including line buffering
	after.c_lflag &= (~ECHO);           // Don't echo characters on the screen (optional)
	tcsetattr (0, TCSANOW, &after); // Set the modified flags

	char c;
	cin.get(c);
	while (cin.good())
	{
		cout << c << endl;
		cin.get(c);
	}

	// restore termios state
	tcsetattr (0, TCSANOW, &before);
	return 0;
}