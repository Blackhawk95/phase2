/*
 * Empty C++ Application
 */

#include <xparameters.h>
#include <xmem.h>
#include "platform.h"
#include <stdio.h>
#include "QofQueue.h"
#include "mes_mem.h"
#include <iostream>

//data
#include "final_out_wr.h"
//#include "hai.h"
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
	/*printf(" hello\n");
	scanf("%hu",&arrn[0][0]);
	scanf("%hu",&arrn[0][1]);
	scanf("%hu",&arrn[0][2]);
	printf("%hu\n",arrn[0][0]);
	printf("%hu\n",arrn[0][1]);
	printf("%hu\n",arrn[0][2]);


	*/
	for(long int i = 0;i < INST_SIZE;i++){
	      arrn[i][0] = (arr[i][0] & 0xFFFF);
	      arrn[i][1] = arr[i][1];  //(int8);
	      arrn[i][2] = arr[i][2];
	}

	for(long int i = 0;i< INST_SIZE;i++){
	//while(true){

		/*printf(" hello\n");
		scanf("%lld",&arrn[0][0]);
		scanf("%lld",&arrn[0][1]);
		scanf("%lld",&arrn[0][2]);
		printf("%lld\n",arrn[0][0]);
		printf("%lld\n",arrn[0][1]);
		printf("%lld\n",arrn[0][2]);
		long int i = 0;*/
	      initSignal(&signal);
	      //printf("%ld\t",i);
	      if(arrn[i][1] == 1){
	    	  std::cout<<(int)signal.ma<<"\n";
		    qoq.write(arrn[i][0],&signal);
		    std::cout<<signal.ma<<"\n";
	        if(signal.write){ //DATA too
	          if(signal.writeBack){ //00 - writeback

	        	//XMem_Set_a_V(&doMem,arrn[i][0]);
	        	XMem_Set_a_V(&doMem,arrn[i][0]);
	        	XMem_Set_ma_V(&doMem,signal.ma);
	        	XMem_Set_flag_V(&doMem,0x00);
	        	//XMem_Set_data_V_i(&doMem,data);

	        	XMem_Start(&doMem);
	        	while(!XMem_IsDone(&doMem));
	        	while(!XMem_IsReady(&doMem));

	            printf("[WB] MA %d, WriteBackAddress: %lld\n",signal.ma,signal.mmA);
	          }
	          //10 - write
	          XMem_Set_a_V(&doMem,arrn[i][0]);
	          XMem_Set_ma_V(&doMem,signal.ma);
	          XMem_Set_flag_V(&doMem,0x02);
	          XMem_Set_data_V_i(&doMem,arrn[i][2]);

	          XMem_Start(&doMem);
	          while(!XMem_IsDone(&doMem));
	          while(!XMem_IsReady(&doMem));


	          printf("[W] MA %d, NewAddress: %lld, Data: %lld\n",signal.ma,arrn[i][0],arrn[i][2]);
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
	            while(!XMem_IsReady(&doMem));
	            //std::cout<<(int)signal.ma<<"\n";
	        printf("[R_DRAM] MiniAddress: %d Data from MA %lu\n",signal.ma,XMem_Get_data_V_o(&doMem));
	        }
	        else if(signal.read_from_nvm){
	        	XMem_Set_a_V(&doMem,arrn[i][0]);
	        	XMem_Set_ma_V(&doMem,signal.ma);
	        	XMem_Set_flag_V(&doMem,0x01);

		        XMem_Start(&doMem);
		        while(!XMem_IsDone(&doMem));
		        while(!XMem_IsReady(&doMem));

	           printf("[R_NVM] Address: %lld Data from MA %lu\n",arrn[i][0],XMem_Get_data_V_o(&doMem));
	        }
	      }
	}

	//Hardware code
	//printf(" Hello\n");
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
