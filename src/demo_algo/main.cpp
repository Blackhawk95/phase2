#include <iostream>
#include "csv.h"
#include "register.h"

int main(){

	//std::cout<<csv_extract("hai.csv", 5)<<endl;
	Register R;

	long int arr[16] = { 1234, 5678, 1235, 9012, 1236, 8000, 3001, 1235, 1236, 1237, 8001, 9013, 9014,
						8025, 6012, 1234};
	
	for( int i = 0; i < 15; i++ ){
		R.logPrintTrac();
		printf("%ld\n",arr[i]);
		R.insert(arr[i]);
	}
	return 0;
}