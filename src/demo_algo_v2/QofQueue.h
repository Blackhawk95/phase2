#ifndef QOFQUEUE_H
#define QOFQUEUE_H
#define SIZE 64

struct EofEntry{
	Queue q;
	EofEntry* next;
};

struct flagObj{
	long long int addr;
	bool taken;
	bool dump;
};

class QofQueue{
	EofEntry* eoe;
	flagObj flag[SIZE] {};
	int size; 
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
	
};

#endif
