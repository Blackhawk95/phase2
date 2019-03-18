#include "QofQueue.h"
#include <cstdlib>
#include <cstdio>

#define SIZE 8
#define THRESHOLD 500

QofQueue::QofQueue(){
	eoe = NULL;
	size = 0; 
	Queue dump = Queue();
	message m = {0,0,false,false};
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
			//found - so touch corresponding queue TO.DO
			l_present = true;
		} 	
	}

	if(l_present == false){
		//printf("Size : %d\n",size);
		// If the DRAM isn't full
		if(size < SIZE){
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
			size++;			
		}
		//DRAM is full
		else {
			//check if any dump ones exist
			for(int i = 0;i< SIZE;i++){
				if(flag[i].dump == true){ //this indicates, checking for a dump entry
					//prep for message
					m_ma = i;	
					//m_dump = false; //this indicates, replaced a dump entry
				} 	
			}
			if(m_dump == false){ // using it as a flag
				//TO.DO	function - based on age 		
				m_ma = createADump(); //should be implemented by QoQ; -- address passing around may work
				//m_dump = false;
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
	temp->miniAddress = -2;
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
	//Queue qu;
	eoe->q = Queue();
	eoe->next = NULL;
}

Queue* QofQueue::classForNewData(long long int a){
	/*	find the right class
	if class doesn't exist
		make one
	else
		use that
	*/
	struct eofentry* e = eoe;
	struct eofentry* prev = NULL;
	if(e == NULL){
		initEoE();
		return &(eoe->q);
	}
	while(e != NULL){
		//if incoming address exist
		entry* findq = ((e->q).old());
		if(findq->Address <= a + THRESHOLD && findq->Address >= a - THRESHOLD){
			//printf("Loop: %lld :%d\n",findq->Address,a);
			return &(e->q);
		}
		prev = e;
		e = e->next;
	}
	//else, create a new queue in q of queue
	e = (struct eofentry*) malloc (sizeof(struct eofentry));
	e->next = NULL;
	e->q = Queue();
	prev->next = e;
	return &(e->q); 
}

Queue* QofQueue::getQueue(long long int a){
	// just return the queue
	
	struct eofentry* e = eoe;
	if(e == NULL){
		return NULL;
	}

	//	find in dump cause no class found - but there can be a case where found in dump but with class
	for(int i = 0;i< SIZE;i++){
		if(flag[i].addr == a){
			if(flag[i].dump == true){
				printf("Found in Dump\n");
				return &dump;
			}
		}
	}

	while(e != NULL){
		//if incoming address exist
		entry* findq = ((e->q).old());
		if(findq->Address <= a + THRESHOLD && findq->Address >= a - THRESHOLD){
			printf("Loop: %lld :%d\n",findq->Address,a);
			return &(e->q);
		}
		e = e->next;
	}
	
	
	return NULL;
}

void QofQueue::write(long long int a){

	Queue* tempq = classForNewData(a);
	findMiniAddress(a,&m);
	//insert data
	tempq->insert(a,m.m_ma);

}

void QofQueue::read(long long int a){

	int minia=0;
	Queue* tempq = getQueue(a);
	if(tempq == NULL){
		printf("Look at DRAM\n");
		return;
	}
	minia = tempq->getMiniAddressFromQueue(a);
	if(minia == -1){
		printf("data missing in the queue / wrong queue\n");
	}
	else if(minia == -2){
		printf("data found in dump\n");

	}
	else{
		printf("Address: %lld, MiniAddress: %d",a,minia);
	}
}