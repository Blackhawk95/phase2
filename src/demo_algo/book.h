#ifndef BOOK_H
#define BOOK_H
#include <deque>
#include <iterator>
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
    int bookage;
    // int bookage;

    public:
    Book(){}

    void newBookInit(long int a,int ageCounter);
    void newBookInit(entry e);

    long int getBookName();
    long int getBookOldAddress();
    int getBookAge();
    int getBookSize(); 

    void insertEntry(long int a,int ageCounter);
    void insertEntry(entry e);

    int findOldEntry();
    entry deEntry();
    bool alreadyExistingEntry(long int a);
    void deBook();
    int findAndRemoveFromBook(long int a);

    void incBookAge();

    //bools
    bool isEmpty();
    
};
//newBookInit from bare details
void Book::newBookInit(long int a,int ageCounter){
    
    book = a;
    ent.push_back({a,ageCounter});
    booksize = 1;
    bookage = 1;
}

//newBookInit from an entry
void Book::newBookInit(entry e){
    
    book = e.address;
    ent.push_back(e);
    booksize = 1;
    bookage = 1;
}

long int Book::getBookName(){
    return book;
}
//insert a new entry 
void Book::insertEntry(long int a,int ageCounter){
    if(!alreadyExistingEntry(a)){
        ent.push_back({a,ageCounter}); 
        booksize++;
    }
    bookage = 1; // reseting book age
}
//insert a already existing entry
void Book::insertEntry(entry e){
    
    if(!alreadyExistingEntry(e.address)){
        booksize++;
        ent.push_back(e);
    }
    bookage = 1;
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

int Book::getBookAge(){
    return bookage;
}

void Book::incBookAge(){
    bookage++;
}

/* Not implemented this now 
void Book::deBook(){
    while(!ent.empty()){

    }
}*/

int Book::getBookSize(){
    return booksize;
}

int Book::findAndRemoveFromBook(long int a){
    for(auto i = ent.begin();i!=ent.end();i++){
        if((*i).address == a){
            ent.erase(i);
            return 1;
        }
    }
    return 0;
}

bool Book::alreadyExistingEntry(long int a){
    for(auto i = ent.begin();i!=ent.end();i++){
        if((*i).address == a){
            (*i).age = 1;
            return 1;
        }
    }
    return 0;
}


#endif