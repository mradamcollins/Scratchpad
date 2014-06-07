#include <cstdio>
#include <sys/stat.h>
#include <stdlib.h> //Exit
/**
 * A program that checks to see if a file exists by using the sys/stat call
 * to return a struct of file stats
 */
int main(int argc, char *argv[]) {
	if (argc != 2)
	{
		printf("usage: %s <filename>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	struct stat st;
	if(stat(argv[1],&st) == 0) 
	{
		printf("%s is present, its size is: %d\n",argv[1],int(st.st_size));
	} else 
	{
		printf("%s is NOT present!\n", argv[1]);
	}
}
