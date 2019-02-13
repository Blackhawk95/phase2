#include "book.h"
#include <vector>
#define THRESHOLD 1024


class Register{
    std::vector <Book*> reg;
    public:
    Register(){}
    //to generate a new book entry in register
    
    int  insert(long int a);
    void createBook(long int a);
    //TODO: Implement space validation
    void spaceValidate();
};

int  Register::insert(long int a){

    if(reg.empty()){
        createBook(a);
        return 0;
    }
    else{
        for(auto i : reg){
            long int tempA = i->getBookName();
            //checking which book it belongs to
            if(a > tempA - THRESHOLD && a < tempA + THRESHOLD ){
                //book found
                i->insertEntry(a);
                return 1;
            }
        }
        //book not found
        //create a new book
        //but space check should be performed, so
        spaceValidate();
        createBook(a);

    }

}

void Register::createBook(long int a){
    Book *nb = new Book;
    nb->newBookInit(a);
    reg.push_back(nb);
}

void Register::spaceValidate(){
    
}