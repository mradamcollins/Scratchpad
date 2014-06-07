#include "fstream"
#include "iostream"

int main(int argc, char const *argv[])
{
	
	if (argc <2) {
		std::cout << "usage: "<< argv[0] << " <file-name>" << std::endl;
    	return 1;	
	}
	std::string patch_file(argv[1]);
	std::fstream fs (patch_file.c_str(), std::fstream::in);
    if (!fs.is_open()) 
    {
    	std::cout << "file couldn't be opened" << std::endl;
    	return 1;
    }

    int numFeatures;
    fs >> numFeatures;

    std::cout << "Num features: " << numFeatures << std::endl;

	int num1, num2, num3 = 0;
	std::string delim;
    for (int i = 0; i < numFeatures; ++i)
    {
    	fs >> num1 ;
    	if (fs.fail()) { 
    		std::cout << " failed: " <<std::endl;
    		fs >> delim; 
    		continue;
    	}
    	std::cout << num1 <<std::endl;
    }
    fs.close();

	return 0;
}


 