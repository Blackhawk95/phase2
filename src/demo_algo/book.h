#ifndef BOOK_H
#define BOOK_H
#include <deque>
//TODO : age 

struct entry{
    long int address;
    int age;
};

class Book{
    //long int address;
    //may store more than an address
    deque<entry> ent;
    //name of book
    long int book;
    int booksize;
    // int bookage;

    public:
    Book(){}

    void newBookInit(long int a,int ageCounter);
    void newBookInit(entry e);

    long int getBookName();
    long int getBookOldAddress();

    void insertEntry(long int a,int ageCounter);
    void insertEntry(entry e);

    int findOldEntry();
    entry deEntry(); 

    //bools
    bool isEmpty();
};
//newBookInit from bare details
void Book::newBookInit(long int a,int ageCounter){
    
    book = a;
    ent.push_back({a,ageCounter});
    booksize = 1;
}

//newBookInit from an entry
void Book::newBookInit(entry e){
    
    book = e.address;
    ent.push_back(e);
    booksize = 1;
}

long int Book::getBookName(){
    return book;
}
//insert a new entry 
void Book::insertEntry(long int a,int ageCounter){
    ent.push_back({a,ageCounter}); 
    booksize++;
}
//insert a already existing entry
void Book::insertEntry(entry e){
    booksize++;
    ent.push_back(e);
}

int Book::findOldEntry(){
    return ent.front().age; 
}

entry Book::deEntry(){
    booksize--;
    entry temp = ent.front();
    ent.pop_front();
    return temp;
}

bool Book::isEmpty(){
    if(ent.empty()){
        return true;
    }
    return false;
}

long int Book::getBookOldAddress(){
    return ent.front().address;
}

#endif