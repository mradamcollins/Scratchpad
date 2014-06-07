#include <iostream>
#include <map>

int main(int argc, char *argv[])
{
    std::cout << "Hello World!" << std::endl;
    std::map<char, int> mymap;
    std::map<char, int>::iterator it;

    mymap['a'] = 50;
    mymap['b'] = 100;
    mymap['c'] = 150;
    mymap['d'] = 200;

    it = mymap.begin();
    std::cout << "Begin" << std::endl;
    std::cout << "first: " << it->first << " second: " << it->second << std::endl;

    std::cout << "it++" << std::endl;
    it++;
    std::cout << "first: " << it->first << " second: " << it->second << std::endl;


    return 0; //success
}


