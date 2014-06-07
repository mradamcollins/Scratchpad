#include <iostream>
#include <string>

using namespace std;

struct Container
{

	operator string() const {
		return "String";		
	}

	explicit operator bool() {
		return true;
	}
};

int main(int argc, char const *argv[])
{

	Container c;
	string t("test");
	cout << t << endl;
	if (c) {
		cout << "true" << endl;		
	} else {
		cout << "false" << endl;
	}

	
	cout << (string)c << endl;
	return 0;
}