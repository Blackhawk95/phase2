#include <fstream>

using namespace std;

std::string csv_extract(const char* filename,int num){

	ifstream infile(filename);
	std::string line;
	while(num--){
		if(!std::getline(infile, line)) return 0;
	}

	return line;
}
