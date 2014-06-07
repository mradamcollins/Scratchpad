#include <iostream>
#include <map>

// a templated function to return the size of an array 
template< typename T, size_t N>
size_t ArraySize( T(&)[N] ) 
{
	return N;
};

void show(bool array[], size_t num_elements)
{
	for (int i = 0; i < num_elements ; ++i)
	{
		std::cout << i << ": " << array[i] << std::endl;
	}
};

/**
 * Test program to demostrate the initialisation syntax used for
 * arrays. The confusion was over why all values of a bool array
 * could be initialised to zero, but only the first one could be
 * initialised to 1. 
 * 
 * The answer is that initialisation using {} is index based, 
 * meaning only the n'th element in th {} is initialised all 
 * others used the default initialiser ( which is 0 for bools )
 *
 * To initialise an entire array, you can use std::fill_n
 */
int main(int argc, char* argv[])
{
	bool array_a[4];
	std::cout << "UnInitialised" << std::endl;
	show(array_a, ArraySize(array_a));

	bool array_b[4]={0}; 
	std::cout << "Init to 0" << std::endl;
	show(array_b, ArraySize(array_b));

	bool array[4] = {1};
	std::cout << "Init to 1" << std::endl;
	show(array, ArraySize(array));

	std::cout << "Filled" << std::endl;
	std::fill_n(array,ArraySize(array),1);
	show(array, ArraySize(array));
	return 0; //success
}


