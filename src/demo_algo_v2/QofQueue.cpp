#include "QofQueue.h"
#include <cstdlib>
#include <cstdio>

#define SIZE 8
#define THRESHOLD 500
#define DUMPLIMIT 4

QofQueue::QofQueue(){
	eoe = NULL;
	size = 0;
	Queue dump = Queue();
	message m = {0,0,false,false};
	dumptrigger = 0;
	exists = false;
}

/*
 *
 * Deals with finding mini address available by loookin at the flag
 * directory
 * */

void QofQueue::findMiniAddress(long long a,message* mptr){
	//printf("QofQueue : findMiniAddress | Flag A\n");
	//have to convert this into a message format
	long long m_addr = a;
	bool m_taken = false;
	bool m_dump = false;
	int m_ma = -1;

	bool l_present = false;
	bool l_dumpfoundflag = false;

	// Address already on the DRAM
	for(int i = 0;i< SIZE;i++){
		if(flag[i].addr == a){
			//found - so touch corresponding queue TO.DO
			//if a data with same address exist in dump, remove the data from dump and proceed with an insert
			//instead of touch, also remove the dump entry
			if(flag[i].dump == true){
				//This is a hack to remove an element from the queue
					dump.touch(i);
					dump.removeTail();
			}else{
				exists = true;
			}
			m_ma = i;
			l_present = true;
			m_taken = true;
			m_dump = false;
		}
	}
//printf("QofQueue : findMiniAddress | Flag B\n");
	if(l_present == false){
		//printf("QofQueue : findMiniAddress | Flag C\n");
		//printf("Size : %d\n",size);
		// If the DRAM isn't full
		if(size < SIZE){
			for(int i = 0;i< SIZE;i++){
				//find an empty location
				if(flag[i].taken == false){
					//prep for the message
					m_ma = i;
					m_taken = true;
					m_dump = false;
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
			//printf("QofQueue : findMiniAddress | Flag D\n");
			//m_dump = true;
			//check if any dump ones exist
			for(int i = 0;i< SIZE;i++){
				if(flag[i].dump == true){ //this indicates, checking for a dump entry
					//prep for message
					m_ma = i;
					m_dump = false; //this indicates, replaced a dump entry
					m_taken = true;
					//printf("Address: %lld\n",a);
					l_dumpfoundflag = true;
					dumpWriteBack(i);
					break;
				}
			}
			//printf("QofQueue : findMiniAddress | Flag E\n");
			if(l_dumpfoundflag != true){ // using it as a flag
				//m_ma = createADump(); //should be implemented by QoQ; -- address passing around may work
				m_ma = performWriteBack();
				m_dump = false;
				m_taken = true;
				//m_dump = false;
			}
			//printf("QofQueue : findMiniAddress | Flag F\n");
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
/* NOT NEEDED NOW, NEED IN FUTURE
int QofQueue::createADump(){
	int tempma;
	struct entry* temp = old()->old();
	tempma = temp->miniAddress;
	temp->miniAddress = -2;
	dump.insert(temp); // this handles edge cases inside
	old()->remove();
	return tempma;
}*/

/*
 * Writeback instantly sends message to release the oldest memory location
 * and returns its mini address
 * */

int QofQueue::performWriteBack(){
	int tempma;
	//printf("QofQueue : performWriteBack | Flag A\n");
	struct entry* temp = old()->old();
	tempma = temp->miniAddress;
	//printf("QofQueue : performWriteBack | Flag B\n");
	writeBack(temp);
	//printf("QofQueue : performWriteBack | Flag C\n");
	return tempma;
}

/*
 * This is a temporary writeback function - for now it prints only
 * */

void QofQueue::writeBack(entry* we){
	printf("Writing back to main memory Address : %lld, from MA: %d\n",we->Address,we->miniAddress);
	//printf("QofQueue : writeBack | Flag A.1\n");
	int fl = old()->remove();
	//printf("QofQueue : writeBack | Flag A.2\n");
	if(fl == -1){
		//printf("QofQueue : writeBack | Flag B\n");
		struct eofentry* temp = old_eoe();
		struct eofentry* temp2 = temp->next;
		temp->q = temp2->q;
		temp->next = temp2->next;
		free(temp2);
		//halve the dumptrigger
		dumptrigger = dumptrigger / 2;
	}
	//printf("QofQueue : writeBack | Flag C\n");
}

void QofQueue::dumpWriteBack(int ma){
	entry* tempe = dump.old();
	//printf(" dumpWriteBack(%d) ",ma);
	if(tempe == NULL){
		printf("ERROR: NOT FOUND 1\n");
		return;
	}
	if(tempe->next == NULL && tempe->miniAddress == ma){
		printf("Writing back to main memory Address : %lld, from DUMP\n",tempe->Address);
		free(tempe);
		dump = Queue();
		return;
	}
	else if(tempe->next == NULL && tempe->miniAddress != ma){
		printf("ERROR: NOT FOUND 2\n");
		return;
	}
	if(tempe->miniAddress == ma){
		printf("Writing back to main memory Address : %lld, from DUMP\n",tempe->Address);
		entry* tempe3 = tempe->next;
		tempe->Address = tempe3->Address;
		tempe->miniAddress = tempe3->miniAddress;
		tempe->next = tempe3->next;
		free(tempe3);
		return;
	}
	while(tempe->next!=NULL){
		if(tempe->next->miniAddress == ma){
			printf("Writing back to main memory Address : %lld, from DUMP, having MA: %d\n",tempe->next->Address,
				tempe->next->miniAddress);
			struct entry* tempe2 = tempe->next;
			tempe->next = tempe2->next;
			free(tempe2);
			return;
		}
		tempe = tempe->next;
	}
	if(tempe->miniAddress == ma){
		printf("Writing back to main memory Address : %lld, from DUMP\n",tempe->Address);
		return;
	}
	printf("ERROR: NOT FOUND 3 : MIniAddress : %d tempe->miniAddress = %d \n", ma,tempe->miniAddress);
	return;
}

/*
 * Old queue = Entry of Entry
 * */

Queue* QofQueue::old(){
    if(eoe == NULL){
			  printf("QofQueue : old() | EOE is NULL\n");
        return NULL;
    }
    else{
        struct Queue* head = &(eoe->q);
        return head;
    }
}

eofentry* QofQueue::old_eoe(){
	if(eoe == NULL){
		return NULL;
	}
	else{
		return eoe;
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
	int dumptriggerflag = 0;
	if(e == NULL){
		initEoE();
		//printf("a");
		return (eoe);
	}
	while(e != NULL){
		//if incoming address exist
		//printf("\t\t Problem after queue movement : %lld \t\n",(e->q).old()->Address);
		entry* findq = ((e->q).old());

		if(findq->Address <= a + THRESHOLD && findq->Address >= a - THRESHOLD){
			//printf("Loop: %lld :%lld\n",findq->Address,a);
			//printf("b");
			//move the queue to the end/ indicating the update

			if(dumptriggerflag == 0){ //if its the oldest that gets updated, then halve the dumptrigger
				dumptrigger = dumptrigger/2;
			}
			else { // else add 1 to the dumptrigger
				dumptrigger++;
			}
			//printf("HAHA %d\n",((e->q).old())->miniAddress);
			return (e);
		}
		dumptriggerflag++;

		prev = e;
		e = e->next;
	}
	//else, create a new queue in q of queue
	e = (struct eofentry*) malloc (sizeof(struct eofentry));
	e->next = NULL;
	e->q = Queue();
	prev->next = e;
	//printf("c");
	dumptrigger++;
	return (e);
}

/*
 * This function moves the given eoe to the back of the list
 * */
eofentry* QofQueue::updateQofQueue(eofentry* ce){
	//printf(" Flag\n");
	if(ce !=NULL && ce->next != NULL ){
		//printf(" Flag A\n");
		struct eofentry* neweoe = (struct eofentry*)malloc(sizeof(&ce));
		//printf("size of eoe- %ld\n",sizeof(&ce));
		//create a copy
		neweoe->q = ce->q;
		neweoe->next = NULL; //ce->next;

		//printf(" Flag B\n");
		//made a pointer to neighbour
		struct eofentry* tempe = NULL;
		tempe = ce->next;

		//printf(" Flag C\n");
		//copy the data from next to current
		ce->q = tempe->q;
		ce->next = tempe->next;

		//freeing the next
		free(tempe);

		//printf(" Flag D\n");
		struct eofentry* te = ce;
		/*
		if(te->next == NULL){
			printf("FLAG (((())))\n");
			printf("%llx -> %d\n",neweoe,((neweoe->q).old())->miniAddress);
		}*/
		//connect the copy to end of the eoe queue;
		while(te->next!=NULL){
				te = te->next;
		}
		//printf(" Flag E\n");
		te->next = neweoe;
		//printf("%d -- %llx\n",((te->q).old())->miniAddress,ce);
		//printf(" Flag F\n");
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
				//printf("Found in Dump\n");
				return &dump;
			}
		}
	}

	while(e != NULL){
		//if incoming address exist
		entry* findq = ((e->q).old());
		if(findq->Address <= a + THRESHOLD && findq->Address >= a - THRESHOLD){
			//printf("Loop: %lld :%d\n",findq->Address,a);
			return &(e->q);
		}
		e = e->next;
	}
	return NULL;
}

void QofQueue::dumptriggercheck(){
	//printf("DumpTrigger: %d\n",dumptrigger);
	if(dumptrigger >= DUMPLIMIT){
		//MOVE the eoe's queue to
		//printf("bhhaahhahha: %d\n",dumptrigger);
		eofentry* tempe = eoe;
		eofentry* e = eoe->next;

		entry* en = (&(tempe->q))->old();
		entry* tempen = en;
		while(tempen != NULL){
			flag[tempen->miniAddress].dump = true;
			//tempen->miniAddress = -5;
			tempen = tempen->next;
		}
		//printf("DUMPTRIGGER LOG, MA OF FIRST: %d\n",en->miniAddress);
		dump.insert(en); // copy the initial entry to dump and let it insert there
		eoe = e;
		//eoe->next = tempe->next;
		//printf("D\n");
		free(tempe);
		dumptrigger = 0;
	}

}

void QofQueue::write(long long int a){

	findMiniAddress(a,&m);
	//printf(" Step 1 complete\n");
	eofentry* tempq = classForNewData(a);
	//printf(" Step 2 complete\n");
	tempq = updateQofQueue(tempq);
	//printf(" Step 3 complete %d\n",m.m_ma);
	//insert data
	if(exists){ //if already existing
		(&(tempq->q))->touch(m.m_ma);
		exists = false;
	}
	else //else insert
		(&(tempq->q))->insert(a,m.m_ma);
	//printf(" Step 4 complete\n");
	dumptriggercheck();
	//printf(" Step 5 complete\n");

}

void QofQueue::read(long long int a){

	int minia=0;
	Queue* tempq = getQueue(a);
	if(tempq == NULL){
		//printf("Look at DRAM\n");
		return;
	}
	minia = tempq->getMiniAddressFromQueue(a);
	if(minia == -1){
		//printf("data missing in the queue, check / wrong queue\n");
	}
	else if((flag[minia].dump == true)){
		//printf("data found in dump, Address: %lld\n",a);
	}
	else{
		//printf("Address: %lld, MiniAddress: %d\n",a,minia);
	}
}

void QofQueue::clean(){
	while(eoe != NULL){
		(eoe->q).clean();
		eofentry* next = eoe;
		eoe = eoe->next;
		free(next);
	}
}

void QofQueue::logFlag(){
	printf("___________________________________\n");
	printf(" miAdd\tAdd\tDmp\tTkn\n");
	for (int i = 0;i < SIZE;i++){
		printf(" %d\t%lld\t%d\t%d\n",i,flag[i].addr,flag[i].dump,flag[i].taken);
	}
	printf("___________________________________\n");
}

void QofQueue::logQofqueue(){
	printf("___________________________________\n\n");
	eofentry* tempeoe = eoe;
	while(tempeoe != NULL){
		Queue* tempq = &(tempeoe->q);
		entry* tempe = tempq->old();
		printf(" #");
		while(tempe != NULL){
			printf("-> %d ",tempe->miniAddress);
			tempe = tempe->next;
		}
		printf("\n |\n");
		tempeoe = tempeoe->next;
	}
	printf(" NULL\n");
	printf("___________________________________\n");
}
