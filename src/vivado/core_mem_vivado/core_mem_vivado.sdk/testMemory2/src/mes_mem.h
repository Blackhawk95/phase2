#ifndef MESMEM_H
#define MESMEM_H

#include <stdint.h>

#define SIZE 64
#define THRESHOLD 500
#define DUMPLIMIT 16
#define PRINTADD "%d"
#define INST_SIZE 3000

typedef /*long long int*/ uint16_t addr_uint;
typedef uint8_t int8;


struct mes_mem
{
    /* data */
    uint16_t miA;
    uint16_t mmA;
    uint8_t ma;
    bool writeBack;
    bool write;
    bool read_from_nvm;
    bool read_from_dram;
};
#endif
