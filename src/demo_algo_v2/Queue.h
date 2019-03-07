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
    void remove();
    entry* old();
    void touch(int ma);
    
    //flag checks
    bool isEmpty();
};
#endif
