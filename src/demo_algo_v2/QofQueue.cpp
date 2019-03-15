#include "QofQueue.h"
#include <cstdlib>
#include <cstdio>

#define SIZE 64
#define THRESHOLD 1000

QofQueue::QofQueue(){
}

/*
 *
 * Deals with finding mini address available by loookin at the flag
 * directory
 * */

void QofQueue::findMiniAddress(long long a,message* mptr){
	
	//have to convert this into a message format
	long long m_addr = a;
	bool m_taken = false;
	bool m_dump = false;
	int m_ma = -1;

	bool l_present = false;
	
	// Address already on the DRAM
	for(int i = 0;i< SIZE;i++){
		if(flag[i].addr == a){
			//found - so touch corresponding queue
			l_present = true;
		} 	
	}

	if(l_present == false){
		// If the DRAM isn't full
		if(size != 64){
			for(int i = 0;i< SIZE;i++){
				//find an empty location
				if(flag[i].taken == false){
					//prep for the message				
					m_ma = i;
					m_taken = true;
					break;
				} 
			}
			if(m_ma == -1){
				printf(" Something is wrong :: find MINI Address \n");		
			}							
		}
		//DRAM is full
		else {
			//check if any dump ones exist
			for(int i = 0;i< SIZE;i++){
				if(flag[i].dump != false){
					//prep for message
					m_ma = i;	
					m_dump = true;
				} 	
			}
			if(m_dump == false){
				//TO.DO	function - based on age 		
				m_ma = createADump(); //should be implemented by QoQ; -- address passing around may work
				m_dump = true;
			}
		}
	}
	//updateFlag();
	//Updates the flag
	flag[m_ma] = {m_addr,m_taken,m_dump};

	//setting message
	mptr->m_addr=m_addr;
	mptr->m_dump=m_dump;
	mptr->m_taken=m_taken;
	mptr->m_ma=m_ma;
}

/*
void QofQueue::updateFlag(){
	flag[m_ma] = {m_addr,m_taken,m_dump};
}*/

/*
 * Deals with moving an old entry in QoQ and returning the mini address
 **/

int QofQueue::createADump(){
	int tempma;
	struct entry* temp = old()->old();
	tempma = temp->miniAddress;
	dump.insert(temp); // this handles edge cases inside
	old()->remove();
	return tempma;
}





/*
 * Old queue = Entry of Entry
 * */

Queue* QofQueue::old(){
    if(eoe == NULL){
        return NULL;
    }
    else{
        struct Queue* head = &(eoe->q);
        return head;
    }
}

void QofQueue::initEoE(){
	eoe = (struct eofentry*) malloc (sizeof(struct eofentry)); 
}

Queue* QofQueue::classForNewData(long long int a){
	/*	find the right class
	if class doesn't exist
		make one
	else
		use that
	*/
	struct eofentry* e = eoe;
	if(e == NULL){
		initEoE();
		return &(eoe->q);
	}
	while(e != NULL){
		//if incoming address exist
		if(e->q.old()->Address <= a + THRESHOLD || e->q.old()->Address >= a - THRESHOLD){
			return &(e->q);
		}
	}
	//else, create a new queue in q of queue
	e = (struct eofentry*) malloc (sizeof(struct eofentry)); 
	return &(e->q); 
}


void QofQueue::write(long long int a, message* mptr){

	Queue* tempq = classForNewData(a);
	findMiniAddress(a,mptr);
	//insert data
	tempq->insert(a,mptr->m_ma);

}

void QofQueue::read(long long int a,message* mptr){

	Queue* tempq = getQueue(a);

}