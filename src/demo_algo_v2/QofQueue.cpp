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
			//m_dump = true;
			//check if any dump ones exist
			for(int i = 0;i< SIZE;i++){
				if(flag[i].dump == true){ //this indicates, checking for a dump entry
					//prep for message
					m_ma = i;	
					m_dump = false; //this indicates, replaced a dump entry
				} 	
			}
			if(m_dump == false){ // using it as a flag
				//TO.DO	function - based on age 		
				//m_ma = createADump(); //should be implemented by QoQ; -- address passing around may work
				m_ma = performWriteBack();
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
 * Writeback instantly sends message to release the oldest memory location
 * and returns its mini address
 * */

int QofQueue::performWriteBack(){
	int tempma;
	struct entry* temp = old()->old();
	tempma = temp->miniAddress;
	writeBack(temp);
	return tempma;
}

/*
 * This is a temporary writeback function - for now it prints only
 * */

void QofQueue::writeBack(entry* we){
	printf("Writing back to main memory Address : %lld, from MA: %d\n",we->Address,we->miniAddress);
	old()->remove();
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

eofentry* QofQueue::classForNewData(long long int a){
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
		printf("a");
		return (eoe);
	}
	while(e != NULL){
		//if incoming address exist
		//printf("\t\t Problem after queue movement : %lld \t\n",(e->q).old()->Address);
		entry* findq = ((e->q).old());
		if(findq->Address <= a + THRESHOLD && findq->Address >= a - THRESHOLD){
			printf("Loop: %lld :%d\n",findq->Address,a);
			//move the queue to the end/ indicating the update
			printf("b");
			return (e);
		}
		prev = e;
		e = e->next;
	}
	//else, create a new queue in q of queue
	e = (struct eofentry*) malloc (sizeof(struct eofentry));
	e->next = NULL;
	e->q = Queue();
	prev->next = e;
	printf("c");
	return (e); 
}

/*
 * This function moves the given eoe to the back of the list
 * */
eofentry* QofQueue::updateQofQueue(eofentry* ce){
	printf(" Flag\n");
	if(ce !=NULL && ce->next != NULL ){
		printf(" Flag A\n");
		struct eofentry* neweoe = (struct eofentry*)malloc(sizeof(&ce));
		//printf("size of eoe- %d\n",sizeof(&ce));
		//create a copy 
		neweoe->q = ce->q;
		neweoe->next = NULL; //ce->next;

		printf(" Flag B\n");
		//made a pointer to neighbour
		struct eofentry* tempe = NULL;
		tempe = ce->next;

		printf(" Flag C\n");
		//copy the data from next to current
		ce->q = tempe->q;
		ce->next = tempe->next;

		//freeing the next
		free(tempe);

		printf(" Flag D\n");
		struct eofentry* te = ce;
		
		//connect the copy to end of the eoe queue;
		while(te!= NULL && te->next!=NULL){
				te = te->next;
		}
		printf(" Flag E\n");
		te->next = neweoe;
		te = te->next;
		return te;
	}
	if(ce == NULL)
		printf("ERROR: an empty queue");	
	return ce;
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

	eofentry* tempq = classForNewData(a);
	printf(" Step 1 complete\n");
	updateQofQueue(tempq);
	findMiniAddress(a,&m);
	//insert data
	(&(tempq->q))->insert(a,m.m_ma);

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