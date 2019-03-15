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

struct message{
	long long int m_addr;
	int m_ma;
	bool m_taken;
	bool m_dump;
};


class QofQueue {
	eofentry* eoe;
	flagObj flag[SIZE] {};
	int size; 
	Queue dump;
	message m;
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

	

	//ops
	void findMiniAddress(long long int a, message* mptr);
	void updateFlag();
	int createADump();
	Queue* classForNewData(long long int a); //if empty, make a new
	void initEoE();
	void write(long long a,message* mptr); //use this after findMiniAddress to get ma

	//QoQueue related ops
	Queue* old();
};

#endif
