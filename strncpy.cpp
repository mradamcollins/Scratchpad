#include <iostream>

char* strncpy(char* destination, const char* source, size_t num)
{
    int numCopied = 0;
    char* dest = destination;
    while (numCopied < num)
    {
        *dest = *source;
        if (*source == '\0') 
        {
            break;
        }
        ++dest;
        ++source;
        ++numCopied;
    }
    return destination;
}

int main(int argc, char const *argv[])
{
	char src[20] = {"hello world"};
	char dst[20];
	char * dst_ptr; 
	std::cout << "src:  " << src << std::endl << "dest: " << dst << std::endl;
	dst_ptr = strncpy(dst, src, 7);
	std::cout << "src:  " << src << std::endl << "dest: " << dst << std::endl;
	return 0;
}