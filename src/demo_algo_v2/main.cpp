#include <iostream>
//#include "Queue.h"
#include "QofQueue.h"

int main(){
    QofQueue qoq;
    qoq.write(1000);
    qoq.write(2000);
    qoq.write(3000);
    qoq.write(1001);
    qoq.write(1021);
    qoq.write(2001);
    qoq.write(3001);
    qoq.write(1002);
    qoq.write(2002);
    qoq.write(1012);
    //qoq.write(1003);
    //qoq.write(2003);
    qoq.write(3003); //it fzails TO. DO
    //qoq.read(1000);
    return 0;
}

