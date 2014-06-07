#include <memory>
#include <string.h>
#include <string>
#include <libgen.h>
#include <iostream>

std::string GetDirName(const std::string& fileOrDirName)
{
    const auto freeDeleter = [](char* c) { free(c); };
    std::unique_ptr<char, decltype(freeDeleter)> fileOrDir{strdup(fileOrDirName.c_str()), freeDeleter};
    char* dirName = dirname(fileOrDir.get());
    return {dirName};
}

int main(int argc, char const *argv[])
{
	std::string str("/path/hello");
	std::cout << GetDirName(str) <<std::endl;
	std::cout << str <<std::endl;
	return 0;
}