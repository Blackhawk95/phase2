#include "book.h"
#include <vector>
#include <array>
#define THRESHOLD 1024
#define AGECOUNTERLIMIT 10000
#define BOOKAGELIMIT 100

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
    int ageCounter = 1;

    public:
    Register(){}
    //to generate a new book entry in register
    
    int  insert(long int a);
    void createBook(long int a);
    int tracInsert(long int a);
    int tracDiscarded(long int a);
    Book* findBookWithOldestEntry();
    void createSpace(long int a);
    void ageCounterUpdate();
    void updateBookAge();
    void deleteBookIfAged();
    void removeFromDiscarded(long int a);
    void writeBackToNVM(int i,long int a);
};

int  Register::insert(long int a){


    //TO DO : No need to do this
    if(reg.empty()){
        int ma = tracInsert(a);
        if(ma != -1 || ma >= 64){
            createBook(a);
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
        int ma = tracInsert(a); // this updates the book and creates space
        //check way to make sure new data is inserted into any book
        for(auto i : reg){
            long int tempA = i->getBookName();
            //checking which book it belongs to
            if(a > tempA - THRESHOLD && a < tempA + THRESHOLD ){
                //book found also updates age
                i->insertEntry(a,ageCounter);
                return 1;
            }
        }
        //book not found
        //create a new book
        createBook(a);

    }
    return 0;
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
            writeBackToNVM(i,a);
            removeFromDiscarded(trac[i].address);
            trac[i].address = a;
            trac[i].flag&=(0xFD); // inverted of 0x02
            return i + 64; // found a discarded
        }   
    }
    //couldn't even find a discarded one
    //need to create space
    createSpace(a); // this moves data to dscarded from a queue
    for(int i = 0;i < 64; i++){
        if((trac[i].flag & 0x02) != 1){
            writeBackToNVM(i,a);
            removeFromDiscarded(trac[i].address);
            trac[i].address = a;
            trac[i].flag&=(0xFD); // inverted of 0x02
            return i + 128; // created a discarded and found it
        }   
    }

    //no space found
    return -1;
}

//a function to discard a trac entry
int Register::tracDiscarded(long int a){
    for(int i = 0;i < 64; i++){
                if(trac[i].address == a){
                    //update the d bit on the trac
                    trac[i].flag|=0x02;
                    return 1;
            } 
    }
    return 0;
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

void Register::createSpace(long int a){
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
            tracDiscarded(a);  
        
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

//at every insert age is updated
void Register::updateBookAge(){
    for(auto i : reg){
        i->incBookAge();
    }
}

void Register::deleteBookIfAged(){
    //1. for all books
    for(auto i = reg.begin(); i != reg.end(); i++){    
        //2. find books that aged
        
        if((*i)->getBookAge() > BOOKAGELIMIT){
            //3. while queue is not empty
            while((*i)->getBookSize() > 0){
                //4. remove each entry from book 
                entry temp = (*i)->deEntry();
                //5.  we have to add them to discard queue
                if(discarded.isEmpty()){
                    discarded.newBookInit(temp);
                }
                else
                {
                    discarded.insertEntry(temp);
                }
                //6. and assert the discard flag
                tracDiscarded(temp.address);
            }
            // 7. Now to remove the book entirely
            // didn't manually used delete keyword..I hope its alright
            reg.erase(i);
        }
    }
}

void Register::writeBackToNVM(int i,long int a){
    printf("[writeBackToNVM] %d %ld", i, a);

}

void Register::removeFromDiscarded(long int a){
    if(discarded.findAndRemoveFromBook(a)){
        //Book removed
    }
    else
    {
        printf("[removeFromDiscarded]: Failed to find the book to remove\n");
    }
}