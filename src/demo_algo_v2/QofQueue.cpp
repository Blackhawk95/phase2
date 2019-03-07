#include "QofQueue.h"
#include <cstdio>
#define SIZE 64

QofQueue::QofQueue(){
}

/*
 *
 * Deals with finding mini address available by loookin at the flag
 * directory
 * */

void QofQueue::findMiniAddress(long long a){
	
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