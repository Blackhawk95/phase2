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
    long int getBookName();
    void insertEntry(long int a,int ageCounter);
    int findOldEntry();
};
void Book::newBookInit(long int a,int ageCounter){
    
    book = a;
    ent.push_back({a,ageCounter});
    booksize = 1;
}
long int Book::getBookName(){
    return book;
}

void Book::insertEntry(long int a,int ageCounter){
    ent.push_back({a,ageCounter}); 
    booksize++;
}

int Book::findOldEntry(){
    return ent.front().age; 
}

#endif