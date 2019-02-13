#include <iostream>
#include "csv.h"
#include "classify.h"


int main(){

	std::cout<<csv_extract("hai.csv", 5)<<endl;
	return 0;
}