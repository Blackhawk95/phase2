#ifndef QOFQUEUE_H
#define QOFQUEUE_H

#include "Queue.h"
#include "mes_mem.h"

#define SIZE 8

struct eofentry{
	Queue q;
	eofentry* next;
};

struct flagObj{
	addr_uint addr;
	bool taken;
	bool dump;
};

struct message{
	addr_uint m_addr;
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
	int dumptrigger; //dumptrigger is trigger to put older queue into dump
	bool exists;
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
	void findMiniAddress(addr_uint a, message* mptr,mes_mem* signal);
	void updateFlag();
	int createADump();
	eofentry* classForNewData(addr_uint a); //if empty, make a new
	void initEoE();
	Queue* getQueue(addr_uint a);
	int performWriteBack(mes_mem* signal);
	void writeBack(entry* we,mes_mem* signal);
	eofentry* updateQofQueue(eofentry* q);
	void dumptriggercheck();
	void dumpWriteBack(int ma,mes_mem* signal);
	void write(addr_uint a,mes_mem* signal); //use this after findMiniAddress to get ma
	void read(addr_uint a);
	void clean();
	//QoQueue related ops
	Queue* old();
	eofentry* old_eoe();
	//LOGs
	void logFlag();
	void logQofqueue();
	void logDump();
};

#endif
