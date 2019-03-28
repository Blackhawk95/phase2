#include <iostream>
#include <sstream>
#include "csvextract.h"
//#include "register.h"
#include "registerlru.h" // for LRU
//#include "../../testinput.h" //sample input
//#include "../../hai.h"
#include "../../rhai.h"

int main(){

	/* tried to get csv working
	std::string line = csv_extract("hai.csv", 5);//<<endl;
	stringstream addr(line);
	long long int a = 0;
	addr >> a;
	printf("%lld\n",a);
	*/

	Register R;

	//long long int arr[16] = { 1234, 5678, 1235, 9012, 1236, 8000, 3001, 1235, 1239, 1237, 8001, 9013, 9014,
	//					8025, 6012, 1234};

	for( int i = 0; i < 80; i++ ){
		//R.logPrintTrac();
		//printf("%lld\n",arr[i][0]);
		R.insert(arr[i][0]);
	}
	/*
	R.logPrintTrac();
	R.insert(2199012162961);
	*/
	//R.logPrintTrac();
	return 0;
}
