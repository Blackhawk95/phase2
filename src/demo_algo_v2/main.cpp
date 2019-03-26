#include <iostream>
//#include "Queue.h"
#include "QofQueue.h"

int arr[9] = {1000,1001,2000,2001,2002,2003,2005,2006,1003};

int main(){
    QofQueue qoq;

    for(int i = 0;i< 9;i++){
	    qoq.write(arr[i]);
    }
    qoq.read(1001);
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
