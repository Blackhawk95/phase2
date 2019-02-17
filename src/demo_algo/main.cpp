#include <iostream>
#include "csv.h"
#include "register.h"
#include "testinput.h"

int main(){

	//std::cout<<csv_extract("hai.csv", 5)<<endl;
	Register R;

	//long long int arr[16] = { 1234, 5678, 1235, 9012, 1236, 8000, 3001, 1235, 1239, 1237, 8001, 9013, 9014,
	//					8025, 6012, 1234};
	
	for( int i = 0; i < 100; i++ ){
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