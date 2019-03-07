#include "QofQueue.h"
#include <cstdio>
#define SIZE 64

QofQueue::QofQueue(){
}

void QofQueue::findMiniAddress(long long a){
	
	//have to convert this into a message
	long long m_a = 0;
	bool m_taken = false;
	bool m_dump = false;
	int m_ma = 0;

	bool l_present = false;
	
	// Address already on the DRAM
	for(int i = 0;i< SIZE;i++){
		if(flag[i].addr == a){
			//found - so touch corresponding queue
			l_present = true;
			m_a = a;
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
			if(m_ma == 0){
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
				m_ma = createDump(); //should be implemented by QoQ; -- address passing around may work
				m_dump = true;
			}
		}
	}
	updateFlag();
}

void QoQueue::updateFlag(){
	flag[m_ma] = {m_addr,m_taken,m_dump};
}
