/*
 * Empty C++ Application
 */

#include <xparameters.h>
#include <xmem.h>
#include "platform.h"
#include <stdio.h>
#include "QofQueue.h"
#include "mes_mem.h"

//data
#include "final_out_wr.h"
//#include <ap_int.h>


void initSignal(mes_mem* signal){
  signal->writeBack = false;
  signal->write = false;
  signal->read_from_nvm = false;
  signal->read_from_dram = false;
  signal->ma = -1;
  signal->miA = -1;
  signal->mmA = -1;
}



int main()
{
	init_platform();

	//intialize core (mem) - Boilerplate code

	int status;
	XMem doMem;
	XMem_Config *doMem_cfg;
	doMem_cfg = XMem_LookupConfig(XPAR_MEM_0_DEVICE_ID);
	if(!doMem_cfg){
		printf(" Error loading config for doMem_cfg\n");
	}
	status = XMem_CfgInitialize(&doMem,doMem_cfg);
	if(status != XST_SUCCESS){
		printf("Error initializing for doMem\n");
	}

	//initilializing our code
	QofQueue qoq;
	mes_mem signal;

	addr_uint arrn[INST_SIZE][3];
	for(long int i = 0;i < INST_SIZE;i++){
	      arrn[i][0] = (uint16_t)(arr[i][0] & 0xFFFF);
	      arrn[i][1] = (uint8_t)arr[i][1];
	      arrn[i][2] = (uint8_t)arr[i][2];
	}

	for(long int i = 0;i< INST_SIZE;i++){
	      initSignal(&signal);
	      printf("%d\t",i);
	      if(arrn[i][1] == 1){

		      qoq.write(arrn[i][0],&signal);
	        if(signal.write){ //DATA too
	          if(signal.writeBack){ //00 - writeback


	        	XMem_Set_a_V(&doMem,arrn[i][0]);
	        	XMem_Set_ma_V(&doMem,signal.ma);
	        	XMem_Set_flag_V(&doMem,0x00);
	        	//XMem_Set_data_V_i(&doMem,data);

	        	XMem_Start(&doMem);
	        	while(!XMem_IsDone(&doMem));

	            printf("[WB] MA %u, WriteBackAddress: %u\n",signal.ma,signal.mmA);
	          }
	          //10 - write
	          XMem_Set_a_V(&doMem,arrn[i][0]);
	          XMem_Set_ma_V(&doMem,signal.ma);
	          XMem_Set_flag_V(&doMem,0x02);
	          XMem_Set_data_V_i(&doMem,arrn[i][2]);

	          XMem_Start(&doMem);
	          while(!XMem_IsDone(&doMem));

	          printf("[W] MA %u, NewAddress: %u, Data: %u\n",signal.ma,arrn[i][0],arrn[i][2]);
	        }
	      }
	      else if(arr[i][1] == 0){

	        qoq.read(arr[i][0],&signal);
	        if(signal.read_from_dram){
	        	XMem_Set_a_V(&doMem,arrn[i][0]);
	        	XMem_Set_ma_V(&doMem,signal.ma);
	        	XMem_Set_flag_V(&doMem,0x03);

	            XMem_Start(&doMem);
	            while(!XMem_IsDone(&doMem));

	        printf("[R_DRAM] MiniAddress: %u Data from MA %u\n",signal.ma,(int8)XMem_Get_data_V_o(&doMem));
	        }
	        else if(signal.read_from_nvm){
	        	XMem_Set_a_V(&doMem,arrn[i][0]);
	        	XMem_Set_ma_V(&doMem,signal.ma);
	        	XMem_Set_flag_V(&doMem,0x01);

		        XMem_Start(&doMem);
		        while(!XMem_IsDone(&doMem));

	           printf("[R_NVM] Address: %u Data from MA %u\n",arrn[i][0],(int8)XMem_Get_data_V_o(&doMem));
	        }
	      }
	}

	//Hardware code
	printf(" Hello\n");
	/*
	addr_uint a = 1900;
	int8 ma = 54;
	int8 flag = 0x02;
	int8 data = 15;

	XMem_Set_a_V(&doMem,a);
	XMem_Set_ma_V(&doMem,ma);
	XMem_Set_flag_V(&doMem,flag);
	XMem_Set_data_V_i(&doMem,data);
	XMem_Start(&doMem);

	while(!XMem_IsDone(&doMem));

	data = 10;
	flag = 0x03;
	XMem_Set_a_V(&doMem,a);
	XMem_Set_ma_V(&doMem,ma);
	XMem_Set_flag_V(&doMem,flag);
	//XMem_Set_data_V_i(&doMem,data);
	XMem_Start(&doMem);

	while(!XMem_IsDone(&doMem));

	data = XMem_Get_data_V_o(&doMem);
	printf("The result after doing the %d",(char)data);
	*/

    qoq.logFlag();
    qoq.logQofqueue();
    qoq.logDump();
    qoq.clean();
	return 0;
}
