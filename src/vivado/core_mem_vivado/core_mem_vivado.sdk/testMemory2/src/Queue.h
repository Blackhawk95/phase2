#ifndef QUEUE_H
#define QUEUE_H

#include "mes_mem.h"

//typedef /*long long int*/ uint16_t addr_uint;

struct entry{
    addr_uint Address;
    int miniAddress;
    entry* next;
};

class Queue{

    entry* e;

    public:
    Queue();
    void insert(addr_uint a,int ma);
    void insert(entry*);
    int remove();
    entry* old();
    void touch(int ma);
    void removeTail();
    int getMiniAddressFromQueue(addr_uint);
    void clean();
    //flag checks
    bool isEmpty();

};
#endif
