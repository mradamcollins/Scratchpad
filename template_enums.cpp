#include <iostream>
#include <type_traits>
enum class REGA_VALS
{
	VALUE1
};

template<typename R>
void write_reg(R value)
{
	std::cout << "Hello " <<std::endl;
}

int main(int argc, char* argv[])
{
	std::cout << "Hello World!" << std::endl;
	write_reg<REGA_VALS>(REGA_VALS::VALUE1);
	return 0; //success
}


