#include <iostream>
//#include "Queue.h"
#include "QofQueue.h"
//#include "../../dataset/testinput.h"
//#include "../../dataset/hai.h"
#include "../../dataset/final_out_wr.h"
#include "mes_mem.h"

//int arr[] = {1000,1001,2000,2001,2002,2003,2005,2006,1003,1004,1005,3001,3002,2003};

void initSignal(mes_mem* signal){
  signal->writeBack = false;
  signal->write = false;
  signal->read_from_nvm = false;
  signal->read_from_dram = false;
  signal->ma = -1;
  signal->miA = -1;
  signal->mmA = -1;
}

int main(int argc, char** argv){
    QofQueue qoq;
    mes_mem signal;

    int arrn[ INST_SIZE][3];
    // INPUT_DATA_FORMAT : (address >> 6), 0/1 for read/write, count(to get order)

    //taking the last 16 bits only - Hashing
    for(int i = 0;i < INST_SIZE;i++){
      arrn[i][0] = (int)(arr[i][0] & 0xFFFF);
    }


    for(int i = 0;i< INST_SIZE;i++){
      initSignal(&signal);
      if(arrn[i][1] == 1){

	      qoq.write(arrn[i][0],&signal);
        if(signal.write){ //DATA too
          if(signal.writeBack){
            printf("[WB] MA %d, WriteBackAddress: %d\n",signal.ma,signal.mmA);
          }
          printf("[W] MA %d, NewAddress: %d\n",signal.ma,arrn[i][0]);
        }
      }
      else if(arrn[i][1] == 0){

        qoq.read(arrn[i][0],&signal);
        if(signal.read_from_dram){
          printf("[R_DRAM] MiniAddress: %d\n",signal.ma);
        } 
        else if(signal.read_from_nvm){
          printf("[R_NVM] Address: %d\n",arrn[i][0]);
        }
      }    

    }
    qoq.logFlag();
    qoq.logQofqueue();
    qoq.logDump();
    qoq.clean();
    return 0;
}
