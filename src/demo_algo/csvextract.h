#include <fstream>

using namespace std;

string csv_extract(const char* filename,int num){

	ifstream infile(filename);
	string line;
	while(num--){
		if(!getline(infile, line)) return 0;
	}

	return line;
}
