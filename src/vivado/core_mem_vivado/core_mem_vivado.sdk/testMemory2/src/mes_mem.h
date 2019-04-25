#ifndef MESMEM_H
#define MESMEM_H

#include <stdint.h>

#define SIZE 8
#define THRESHOLD 500
#define DUMPLIMIT 4
#define PRINTADD "%d"
#define INST_SIZE 30

typedef long long int addr_uint;
typedef int int8;


struct mes_mem
{
    /* data */
	addr_uint miA;
	addr_uint mmA;
    int ma;
    bool writeBack;
    bool write;
    bool read_from_nvm;
    bool read_from_dram;
};
#endif
