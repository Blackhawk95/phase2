#ifndef QUEUE_H
#define QUEUE_H

struct entry{
    long long int Address;
    int miniAddress;
    entry* next;
};


class Queue{
    
    entry* e;    

    public:
    Queue();
    void insert(long long int a,int ma);
    void insert(entry*);
    int remove();
    entry* old();
    void touch(int ma);
    void removeTail();
    int getMiniAddressFromQueue(long long int);
    void clean();
    //flag checks
    bool isEmpty();
    
};
#endif
