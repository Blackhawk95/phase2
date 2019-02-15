#include "book.h"
#include <vector>
#include <array>
#define THRESHOLD 1024
#define AGECOUNTERLIMIT 10000

struct track{
    long int address;
    int8_t flag; // bit 1 in flag is 0 for empty,
                 // bit 2 in flag is 1 for dirty
};

class Register{
    std::vector <Book*> reg;
    //8bit address or mini-address(ma) is given by register and stored in each entry of
    //book with it.
    Book discarded;
    std::array<track,64> trac{};
    int regsize=0;
    int ageCounter = 1;

    public:
    Register(){}
    //to generate a new book entry in register
    
    int  insert(long int a);
    void createBook(long int a);
    int tracInsert(long int a);
    Book* findBookWithOldestEntry();
    void createSpaceAndInsert(long int a);
    void ageCounterUpdate();
};

int  Register::insert(long int a){

    if(reg.empty()){
        int ma = tracInsert(a);
        if(ma != -1 || ma >= 64){
            createBook(a);
            regsize = 1;
        }
        else //happens when there is no free space
        {   
            //THIS SHOULDN'T HAPPEN
            printf("ma == -1 in empty register : THIS SHOULDN'T HAPPEN");
            exit(0);
        }
        return 0;
    }
    else
    {
        createSpaceAndInsert(a); // this moves data to dscarded from a queue
        int ma = tracInsert(a); // this updates the book and creates space
        //check way to make sure new data is inserted into any book
        for(auto i : reg){
            long int tempA = i->getBookName();
            //checking which book it belongs to
            if(a > tempA - THRESHOLD && a < tempA + THRESHOLD ){
                //book found
                if(regsize < 64){
                    i->insertEntry(a,ageCounter);
                }
                else{
                    //i->getSpace(a);
                }
                return 1;
            }
        }
        //book not found
        //create a new book
        createBook(a);

    }

}

void Register::createBook(long int a){
    Book *nb = new Book;
    nb->newBookInit(a,ageCounter);
    reg.push_back(nb);
}

int Register::tracInsert(long int a){
    //search the entire trac and decide where to put the data
   
    //NEW DATA
    for(int i = 0;i < 64; i++){
        if((trac[i].flag & 0x01) != 1){
            trac[i].address = a;
            trac[i].flag|=0x01;
            return i; // found a space
        }   
    }
    //Check for discarded
    for(int i = 0;i < 64; i++){
        if((trac[i].flag & 0x02) != 1){
            //TODO : CALL WRITEBACK, REMOVE DATA FROM Discarded and PUT new data in queue
            trac[i].address = a;
            trac[i].flag&=(0xFD); // inverted of 0x02
            return i + 64; // found a space
        }   
    }
    //no space found
    return -1;
}
//Book with oldest entry
Book* Register::findBookWithOldestEntry(){
 
     int tempagepos = AGECOUNTERLIMIT;
     int tempageneg = 0;
     int tempage;
     int tempoldage;
     //find smallest
     for(auto i : reg){
         tempage = i->findOldEntry();
         if(tempage >= 0){
             if(tempage < tempagepos){
                 tempagepos = tempage;
             }
         }
         else if(tempage < 0){
             if(tempage < tempageneg){
                 tempageneg = tempage;
             }
         }
     }
     if(tempagepos == AGECOUNTERLIMIT){
         //tempageneg is lowest
         tempoldage = tempageneg;
     }
     else if(tempageneg == 0){
         //tempagepos is lowest
         tempoldage = tempagepos;
     }
     else if (tempagepos == AGECOUNTERLIMIT && tempageneg == 0){
         //impossible or zero entry
     }
     else if(tempagepos != AGECOUNTERLIMIT && tempageneg != 0){
         //temppagepos is lowest
         tempoldage = tempagepos;
     }

     for(auto i : reg){
         if(i->findOldEntry() == tempoldage){
             return i;
         }
     }
     return NULL;
}

void Register::createSpaceAndInsert(long int a){
    //space isnt there
    //need to create space
    //how ?
    //find overall oldest data - directly writeback ( no dirty then writeback )
    //need age variable for each data - linear search 
    //GONE WITH THIS NOW
    //or can check top of every queue - shorter method and also doesnt need a new variable
    
    //ENTIRE BOOK ADDRESS IS PASSED, BOOK NAME would have been enough
    Book* choosenone = findBookWithOldestEntry();

    if(choosenone){
        //getting address from choosenone to select the trac entry - NEED A BETTER SOLUTION
        long int a = choosenone->getBookOldAddress();
        //remove old stuff from boook with old entry
        //and push it into discarded queue
        if(discarded.isEmpty()){
            discarded.newBookInit(choosenone->deEntry());
        }
        else
        {
            discarded.insertEntry(choosenone->deEntry());
        }
        //now update the bits in track
        //find the correct entry on trac
            for(int i = 0;i < 64; i++){
                if(trac[i].address == a){
                    //update the d bit on the trac
                    trac[i].flag|=0x02;
            }   
        }
        
    }
    else{
        printf("ERROR findBookWithOldestEntry() gave NULL\n");
        exit(0);
    }


}


//to update counter perfectly on every insertion
void Register::ageCounterUpdate(){

    //age counter keeps on increasing and once it hit limit,
    //it starts incrementing from -ve of itself
    if(ageCounter < AGECOUNTERLIMIT){
        ageCounter++;
    }
    else
    {
        ageCounter = -(ageCounter-1);
    }
    
}