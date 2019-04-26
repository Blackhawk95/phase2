#include "QofQueue.h"
#include <cstdlib>
#include <cstdio>

QofQueue::QofQueue(int threshold){
	giventhreshold = threshold;
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

void QofQueue::findMiniAddress(addr_uint a,message* mptr,mes_mem* signal){
	//printf("QofQueue : findMiniAddress | Flag A\n");
	//have to convert this into a message format
	addr_uint m_addr = a;
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
					//printf("Address: " " PRINTADD " "\n",a);
					l_dumpfoundflag = true;
					dumpWriteBack(i,signal);
					break;
				}
			}
			//printf("QofQueue : findMiniAddress | Flag E\n");
			if(l_dumpfoundflag != true){ // using it as a flag
				//m_ma = createADump(); //should be implemented by QoQ; -- address passing around may work
				m_ma = performWriteBack(signal);
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

int QofQueue::performWriteBack(mes_mem* signal){
	int tempma;
	//printf("QofQueue : performWriteBack | Flag A\n");
	struct entry* temp = old()->old();
	tempma = temp->miniAddress;
	//printf("QofQueue : performWriteBack | Flag B\n");
	writeBack(temp,signal);
	//printf("QofQueue : performWriteBack | Flag C\n");
	return tempma;
}

/*
 * This is a temporary writeback function - for now it prints only
 * */

void QofQueue::writeBack(entry* we,mes_mem* signal){
	// PRINTLOG
	// printf("Writing back to main memory Address : " PRINTADD ", from MA: %d\n",we->Address,we->miniAddress);
	signal->mmA = we->Address;
	signal->ma = we->miniAddress;
	signal->writeBack = true;
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

void QofQueue::dumpWriteBack(int ma,mes_mem* signal){
	entry* tempe = dump.old();
	//printf(" dumpWriteBack(%d) ",ma);
	if(tempe == NULL){
		printf("ERROR: NOT FOUND 1\n");
		return;
	}
	if(tempe->next == NULL && tempe->miniAddress == ma){
		//PRINTLOG
		//printf("Writing back to main memory Address <> : " PRINTADD ", from DUMP (ma = %d)\n",tempe->Address,ma);
		signal->mmA = tempe->Address;
		signal->ma = ma;
		signal->writeBack = true;
		free(tempe);
		dump = Queue();
		return;
	}
	else if(tempe->next == NULL && tempe->miniAddress != ma){
		printf("ERROR: NOT FOUND 2\n");
		return;
	}
	if(tempe->miniAddress == ma){
		//PRINTLOG 
		//printf("Writing back to main memory Address : " PRINTADD ", from DUMP (ma = %d)\n",tempe->Address,ma);
		signal->mmA = tempe->Address;
		signal->ma = ma;
		signal->writeBack = true;
		entry* tempe3 = tempe->next;
		tempe->Address = tempe3->Address;
		tempe->miniAddress = tempe3->miniAddress;
		tempe->next = tempe3->next;
		free(tempe3);
		return;
	}
	//printf("BLAAHH\n");
	while(tempe->next!=NULL){
		if(tempe->next->miniAddress == ma){
			//PRINTLOG 
			//printf("Writing back to main memory Address : " PRINTADD ", from DUMP, having MA: %d\n",tempe->next->Address,
			//	tempe->next->miniAddress);
			signal->mmA = tempe->next->Address;
			signal->ma = ma;
			signal->writeBack = true;
			struct entry* tempe2 = tempe->next;
			tempe->next = tempe2->next;
			free(tempe2);
			return;
		}
		tempe = tempe->next;
	}
	if(tempe->miniAddress == ma){
		//PRINTLOG 
		//printf("Writing back to main memory Address : " PRINTADD ", from DUMP\n",tempe->Address);
		signal->mmA = tempe->Address;
		signal->ma = ma;
		signal->writeBack = true;
		dump.removeTail();
		return;
	}
	printf("ERROR: NOT FOUND 3 : MIniAddress : %d tempe->miniAddress = %d \n", ma,tempe->miniAddress);
	return;
}

/*
This also works

void QofQueue::dumpWriteBack(int ma){
	printf("Writing back to main memory Address : " PRINTADD ", from DUMP, having MA: %d\n",0,ma);
	dump.touch(ma);
	dump.removeTail();
}*/

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

eofentry* QofQueue::classForNewData(addr_uint a){
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
		//printf("\t\t Problem after queue movement : " PRINTADD " \t\n",(e->q).old()->Address);
		entry* findq = ((e->q).old());

		if(findq->Address <= a + THRESHOLD && findq->Address >= a - THRESHOLD){
			//printf("Loop: " PRINTADD " :" PRINTADD "\n",findq->Address,a);
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

//FIX THIS
void bubbleSort(eofentry* start) 
{ 
    int swapped, i; 
    struct Node *ptr1; 
    struct Node *lptr = NULL; 
  
    /* Checking for empty list */
    if (start == NULL) 
        return; 
  
    do
    { 
        swapped = 0; 
        ptr1 = start; 
  
        while (ptr1->next != lptr) 
        { 
            if (ptr1->data > ptr1->next->data) 
            {  
                swap(ptr1, ptr1->next); 
                swapped = 1; 
            } 
            ptr1 = ptr1->next; 
        } 
        lptr = ptr1; 
    } 
    while (swapped); 
}

/* function to swap data of two nodes a and b*/
void swap(eofentry *a, eofentry *b) 
{ 
    Queue temp;
	temp = a->q; 
    a->q = b->q; 
    b->q = temp; 
} 


/*
 * This function moves the given eoe to the back of the list
 * */
eofentry* QofQueue::updateQofQueue(eofentry* ce){
	//This entire thing will be changed
	/*
	* TODO : SORT IN ASCENDING ORDER ACCORDING TO QUEUESUB : P.S ITS A LINKED LIST :FACEPALM:
	*/


	bubbleSort(eoe);


	/*
	//printf(" Flag\n");
	if(ce !=NULL && ce->next != NULL ){
		//printf(" Flag A\n");
		struct eofentry* neweoe = (struct eofentry*)malloc(sizeof(eofentry));
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

	*/
return ce;
}


Queue* QofQueue::getQueue(addr_uint a){
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
			//printf("Loop: " PRINTADD " :%d\n",findq->Address,a);
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

void QofQueue::write(addr_uint a,mes_mem* signal){

	findMiniAddress(a,&m,signal);
	//printf(" Step 1 complete\n");
	eofentry* tempq = classForNewData(a);
	//printf(" Step 2 complete\n");
	tempq = updateQofQueue(tempq);
	//printf(" Step 3 complete %d\n",m.m_ma);
	//insert data
	signal->ma = m.m_ma;
	if(exists){ //if already existing
		signal->write = true;
		(&(tempq->q))->touch(m.m_ma);
		exists = false;
	}
	else{ //else insert
		signal->write = true;
		(&(tempq->q))->insert(a,m.m_ma);
	}
	//printf(" Step 4 complete\n");
	dumptriggercheck();
	//logDump();	
	//printf(" Step 5 complete\n");
}

void QofQueue::read(addr_uint a,mes_mem *signal){

	int minia=0;
	Queue* tempq = getQueue(a);
	if(tempq == NULL){
		//printf("Look at NVM\n");
		signal->read_from_nvm = true;
		return;
	}
	minia = tempq->getMiniAddressFromQueue(a);
	if(minia == -1){
		//printf("ERROR : data missing in the queue, check / wrong queue\n");
		signal->read_from_nvm = true;
		return;
	}
	else if((flag[minia].dump == true)){
		//printf("data found in dump, Address: " PRINTADD "\n",a);
		signal->ma = minia;
		signal->read_from_dram = true;
		return;
	}
	else{
		//printf("Address: " PRINTADD ", MiniAddress: %d\n",a,minia);
		signal->ma = minia;
		signal->read_from_dram = true;
		return;
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
		printf(" %d\t" PRINTADD "\t%d\t%d\n",i,flag[i].addr,flag[i].dump,flag[i].taken);
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

void QofQueue::logDump(){
	printf("___________________________________\n\n");
	entry* tempe = dump.old();
	printf(" #");
	while(tempe != NULL){
		printf("-> ( %d | " PRINTADD " )",tempe->miniAddress, tempe->Address);
		tempe = tempe->next;
	}
	printf(" -> NULL\n");
	printf("___________________________________\n");
}
