#include <ap_int.h>
#ifndef MAINCODECPP
#define MAINCODECPP
#define BITSNVM 16
#define BITSDRAM 6
#define READ (flag & 0x01) == 0x01
#define DRAM (flag & 0x02) == 0x02
typedef /*long long int*/ ap_int<16> addr_uint;
typedef ap_int<8> int8;


/* Memory module
 *
 * flag - 8 bit - 0x0000_0000
 * LSB 
 * 0 - read/(bar)write
 * 1 - to dram/(bar)to nvm
 * */


//

void mem(addr_uint a,int8 ma,int8 *data,int8 flag){
#pragma HLS INTERFACE s_axilite port=return bundle=CRTL_BUS
#pragma HLS INTERFACE s_axilite port=flag bundle=CRTL_BUS
#pragma HLS INTERFACE s_axilite port=data bundle=CRTL_BUS
#pragma HLS INTERFACE s_axilite port=ma bundle=CRTL_BUS
#pragma HLS INTERFACE s_axilite port=a bundle=CRTL_BUS
    //addr_uint ad = a;
    //int mad = ma;
    //char flagd = flag;

	static int nvm[(1<<BITSNVM)];
	#pragma HLS RESOURCE variable=nvm core=RAM_1P_BRAM
	static int dram[(1<<BITSDRAM)];
	#pragma HLS RESOURCE variable=dram core=RAM_1P_BRAM

    if(READ){
        if(DRAM){
            *data = dram[ma];
        } else {
            *data = nvm[a];
        }
    } else {
        if(DRAM){
            dram[ma] = *data;
        } else {
            nvm[a] = dram[ma]; // the writeback
        }
    }
    //*data = 0;
}
#endif
