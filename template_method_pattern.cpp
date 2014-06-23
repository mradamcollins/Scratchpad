/** Abstract Class that has a template method.
This Method calls abstract methods, thus controlling their ordering and basic structure,
but allowing subclasses to define their internals. **/
#include <iostream>
class AbstractClass
{
public:
	virtual void PrimativeOperation1() = 0;
	virtual void PrimativeOperation2() = 0;
	void DoTemplatMethod() {
		std::cout << "Template Method is enforcing ordering PrimativeOperation2 before PrimativeOperation1" << std::endl;
		PrimativeOperation2();
		PrimativeOperation1();		
	}
};

class ConreteClass : public AbstractClass
{
public:
	virtual void PrimativeOperation1() {
		std::cout << "Operation 1" << std::endl;
	}
	virtual void PrimativeOperation2() {
		std::cout << "Operation 2" << std::endl;
	}
};


int main(int argc, char const *argv[])
{
	ConreteClass myClass;
	myClass.DoTemplatMethod();
	return 0;
}