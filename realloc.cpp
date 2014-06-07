#include <iostream>
#include <cstdlib>
#include <cstdio>

int main(int argc, char* argv[])
{
	std::cout << "Hello World!" << std::endl;
	int count  = 10;
	int * numbers = NULL;
	numbers = (int*) std::calloc (count, sizeof(int));

	// Should print count 0's
	for (int n=0;n<count-1;n++) printf ("%d ",numbers[n]);
	std::cout << std::endl;

	// Realloc the block of memory pointed at by numbers
	int * new_numbers = (int*) std::realloc (numbers , count * sizeof(int));

	// Print numbers again
	for (int n=0;n<count;n++) printf ("%d ",numbers[n]);
	std::cout << std::endl;

	// Free new_numbers
	free(new_numbers);

	return 0; //success
}


