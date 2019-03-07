#ifndef QOFQUEUE_H
#define QOFQUEUE_H

#include "Queue.h"

#define SIZE 64

struct eofentry{
	Queue q;
	eofentry* next;
};

struct flagObj{
	long long int addr;
	bool taken;
	bool dump;
};

class QofQueue {
	eofentry* eoe;
	flagObj flag[SIZE] {};
	int size; 
	Queue dump;
	public:
	/*
		FUNCTIONS
			CREATE A CLASS
			INSERT IN CLASS
	
	
	
		TO.DO outside this qoq
			IF IN CLASS
				GENERATE MINI ADDRESS
				STORE IN CLASS
			NOT IN CLASS
				GENERATE MINI ADDRESS
				CREATE A CLASS	
			
	*/
	QofQueue();
	void findMiniAddress(long long int a);
	void updateFlag();
	int createADump();
	

	//QoQueue related ops
	Queue* old();
};

#endif
