#ifndef QUEUE_H
#define QUEUE_H

#include "mes_mem.h"

typedef /*long long int*/ int addr_uint;

struct entry{
    addr_uint Address;
    int miniAddress;
    entry* next;
};

class Queue{

    entry* e;
    public:
    Queue();
    int queueSub; //EAPR
    void insert(addr_uint a,int ma); //queueSub++;
    void insert(entry*); //queueSub++;
    int remove(); //queueSub--;
    entry* old();
    void touch(int ma); //queueSub++;
    void removeTail(); //queueSub--; ( but this fn is only used for dump)
    int getMiniAddressFromQueue(addr_uint);
    void clean();
    //flag checks
    bool isEmpty();

};
#endif
