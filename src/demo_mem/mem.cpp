//int a[1000];

#define BITSNVM 16
#define BITSDRAM 6
#define READ (flag & 0x01) == 0x01
#define DRAM (flag & 0x02) == 0x02
typedef /*long long int*/ int addr_uint;


/* Memory module
 *
 * flag - 8 bit - 0x0000_0000
 * LSB 
 * 0 - read/(bar)write
 * 1 - to dram/(bar)to nvm
 * */


void mem(addr_uint a,int ma,int data,char flag){
    int nvm[(1<<BITSNVM)];
    int dram[(1<<BITSDRAM)];

    if(READ){
        if(DRAM){//11 - 3
            data = dram[ma];
        } else { //01 - 1
            data = nvm[a];
        }
    } else {
        if(DRAM){//10 - 2 
            dram[ma] = data; 
        } else {//00 - 0
            nvm[a] = dram[ma]; // the writeback
        }
    }
}