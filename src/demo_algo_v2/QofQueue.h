#ifndef QOFQUEUE_H
#define QOFQUEUE_H

#include "Queue.h"

#define SIZE 8

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
	eofentry* classForNewData(long long int a); //if empty, make a new
	void initEoE();
	Queue* getQueue(long long int a);
	int performWriteBack();
	void writeBack(entry* we);
	eofentry* updateQofQueue(eofentry* q);
	void write(long long a); //use this after findMiniAddress to get ma
	void read(long long a);
	//QoQueue related ops
	Queue* old();
};

#endif
