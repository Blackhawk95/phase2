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
    void remove();
    entry* old();
    void touch(int ma);
};

