#include <iostream>
#include "Queue.h"
#include "QofQueue.h"

int main(){
    Queue q;
    q.insert(100,1);
    q.insert(101,2);
	q.insert(102,3);
    q.old();
    q.touch(1);
    q.old();
	q.touch(2);
    q.old();
	q.touch(3);
    q.old();
    return 0;
}

