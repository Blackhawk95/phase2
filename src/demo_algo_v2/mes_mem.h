#ifndef MESMEM_H
#define MESMEM_H

#define SIZE 256
#define THRESHOLD giventhreshold
#define DUMPLIMIT 64
#define PRINTADD "%d"
#define INST_SIZE 60000

struct mes_mem
{
    /* data */
    int miA;
    int mmA;
    int ma;
    bool writeBack;
    bool write;
    bool read_from_nvm;
    bool read_from_dram;
};
#endif
