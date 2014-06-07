#include <iostream>

int addition(int a, int b)
{
	return a + b;
}

int subtraction(int a, int b) 
{
	return a - b;
}

int operation(int a, int b, int (*operation)(int,int)) // define a function that takes a function pointer as a parameter
{
	return (*operation)(a,b); // return the result of the dereferenced function pointer
}

int main(int argc, char const *argv[])
{
	int (*functPointer)(int, int); // define a function pointer 'functPointer' 
	functPointer = addition;		// assign the function addition to the function pointer functPointer
	std::cout << functPointer(1,1) << std::endl;
	functPointer = subtraction;	// assign the function subtraction to the function pointer functPointer
	std::cout << functPointer(1,1) << std::endl;
	std::cout << "==============" << std::endl;
	std::cout << operation(1,1,addition) << std::endl;
	std::cout << operation(1,1,subtraction) << std::endl;
	return 0;
}

