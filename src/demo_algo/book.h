#ifndef BOOK_H
#define BOOK_H
#include <deque>
//TODO : age 

struct entry{
    int address;
};

class Book{
    //long int address;
    //may store more than an address
    deque<entry> ent;
    //name of book
    long int book;

    public:
    Book(){}

    void newBookInit(long int a);
    long int getBookName();
    void insertEntry(long int a);
};
void Book::newBookInit(long int a){
    
    book = a;
    ent.push_back({a});
}
long int Book::getBookName(){
    return book;
}

void Book::insertEntry(long int a){
    ent.push_back({a}); 
}

#endif