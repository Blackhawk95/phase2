#include <iostream>
//#include "Queue.h"
#include "QofQueue.h"
//#include "../../dataset/testinput.h"
#include "../../dataset/hai.h"
#define INST_SIZE 351
//int arr[] = {1000,1001,2000,2001,2002,2003,2005,2006,1003,1004,1005,3001,3002,2003};

int main(int argc, char** argv){
    QofQueue qoq;

    for(int i = 0;i< INST_SIZE;i++){
	    qoq.write(arr[i][0]);
      //qoq.write(arr[i]);
    }

    printf("IA : %lld\n",arr[INST_SIZE][0]);
    qoq.logFlag();
    qoq.logQofqueue();
    /*
    for(int i = 0;i< 11;i++){
	    qoq.read(arr[i]);
    }
    */
    //qoq.read(2006);
    /*
    qoq.write(1000);
    qoq.write(2000);
    qoq.write(3000);
    qoq.write(1001);
    //qoq.write(1021);
    qoq.write(2001);
    qoq.write(3001);
    qoq.write(1002);
    qoq.write(2002);
    qoq.write(3002);
    qoq.write(1003);
    qoq.write(2003);
    qoq.write(3003); //it fzails TO. DO
    //qoq.read(3003);
    //qoq.read(1001);*/
    qoq.clean();
    return 0;
}
