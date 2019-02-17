#include "book.h"
#include <vector>
#include <array>
#define THRESHOLD 1000 //1024
#define AGECOUNTERLIMIT 10000
#define BOOKAGELIMIT 100 //5 //
#define ARRAYSIZE 64 //8

#define LOG false
#define OUTPUT true


struct track{
    long long int address;
    int8_t flag; // bit 1 in flag is 0 for empty,
                 // bit 2 in flag is 1 for dirty
};

class Register{
    std::vector <Book*> reg;
    //8bit address or mini-address(ma) is given by register and stored in each entry of
    //book with it.
    Book discarded;
    std::array<track,ARRAYSIZE> trac{};
    int ageCounter = 1;

    public:
    //Register(){}
    //to generate a new book entry in register
    
    int  insert(long long int a);
    void createBook(long long int a);
    int tracInsert(long long int a);
    int tracDiscarded(long long int a);
    Book* findBookWithOldestEntry();
    void createSpace(long long int a);
    void ageCounterUpdate();
    void updateBookAge();
    void deleteBookIfAged();
    void removeFromDiscarded(long long int a);
    void writeBackToNVM(int i,long long int a);

    //LOGGING PURPOSE
    void logPrintTrac();
};

int  Register::insert(long long int a){


    //TO DO : No need to do this
    if(reg.empty()){
        if(LOG){printf("Entered reg.empty()\n");}
        int ma = tracInsert(a);
        if(ma != -1 || ma >= ARRAYSIZE){
            createBook(a);
        }
        else //happens when there is no free space
        {   
            //THIS SHOULDN'T HAPPEN
            printf("ma == -1 in empty register : THIS SHOULDN'T HAPPEN");
            exit(0);
        }
    }   
    else
    {   if(LOG){printf("Entered register non empty()\n");}
        int ma = tracInsert(a); // this updates the book and creates space
        //check way to make sure new data is inserted into any book
        int flag = 0;
        for(auto i : reg){
            long long int tempA = i->getBookName();
            //checking which book it belongs to
            if(LOG){printf(" i->getBookName() = , %lld < %lld < %lld \n",tempA - THRESHOLD,tempA,tempA + THRESHOLD);}

            if(a > tempA - THRESHOLD && a < tempA + THRESHOLD ){
                //book found also updates age
                //printf("entered\n");
                i->insertEntry(a,ageCounter);
                flag = 1;
                //break;
            }
        }
        //book not found
        //create a new book
        if(flag == 0)
            createBook(a);

    }
    updateBookAge();    
    deleteBookIfAged();
    return 0;
}

void Register::createBook(long long int a){
    Book *nb = new Book;
    nb->newBookInit(a,ageCounter);
    reg.push_back(nb);
}

int Register::tracInsert(long long int a){
    //search the entire trac and decide where to put the data
    if(LOG){printf("Entered tracInsert()\n");}

    //IF same data comes
    for(int i = 0;i < ARRAYSIZE; i++){
        if(trac[i].address == a){
            return -2; // do nothing on trac
        }   
    }

    //NEW DATA
    for(int i = 0;i < ARRAYSIZE; ++i){
        if((trac[i].flag & 0x01) != 1){
            trac[i].address = a;
            trac[i].flag|=0x01;
            if(LOG){printf("Exited tracInsert & found free space\n");}
            return i; // found a space
        }   
    }
    //Check for discarded
    for(int i = 0;i < ARRAYSIZE; ++i){
        if((trac[i].flag & 0x02) == 2){
            writeBackToNVM(i,trac[i].address);
            removeFromDiscarded(trac[i].address);
            trac[i].address = a;
            trac[i].flag&=(0xFD); // inverted of 0x02
            if(LOG){printf("Exited tracInsert & didnot find free space\n");}
            return i + ARRAYSIZE; // found a discarded
        }   
    }
    //couldn't even find a discarded one
    //need to create space
    createSpace(a); // this moves data to dscarded from a queue
    for(int i = 0;i < ARRAYSIZE; i++){
        if((trac[i].flag & 0x02) == 2){
            if(LOG) {
            printf(" : %lld %lld flag = %x",a,trac[i].address,trac[i].flag);
            printf(" flag changed to %x\n", (trac[i].flag)&0xFD);
            }
            writeBackToNVM(i,trac[i].address);
            removeFromDiscarded(trac[i].address);
            trac[i].address = a;
            trac[i].flag&=(0xFD); // inverted of 0x02
            if(LOG){printf("Exited tracInsert & created free space\n");}
            return i + ARRAYSIZE * 2; // created a discarded and found it
        }   
    }

    if(LOG){printf("Exited tracInsert without entering any of the 3 states()\n");}
    //no space found
    return -1;
}

//a function to discard a trac entry
int Register::tracDiscarded(long long int a){
    for(int i = 0;i < ARRAYSIZE; i++){
                if(trac[i].address == a){
                    //update the d bit on the trac
                    //printf("tracdiscarded %lld flag = %x",a,trac[i].flag);
                    trac[i].flag|=0x02;
                    //printf(" flag changed to %x\n", trac[i].flag);
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

void Register::createSpace(long long int a){
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
        if(LOG){printf("the choosen one\n");}
        //getting address from choosenone to select the trac entry - NEED A BETTER SOLUTION
        long long int a = choosenone->getBookOldAddress();
        //remove old stuff from boook with old entry
        //and push it into discarded queue
        if(discarded.isEmpty()){
            if(LOG){printf("Discarded being created\n");}
            discarded.newBookInit(choosenone->deEntry());
        }
        else
        {   if(LOG){printf("Discarded being inserted data\n");}
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
        //printf("WEEEBOOOOOOO %d\n",(*i)->getBookAge());
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

void Register::writeBackToNVM(int i,long long int a){
    if(OUTPUT){printf("[writeBackToNVM] %d %lld\n", i, a);}

}

void Register::removeFromDiscarded(long long int a){

    if(!discarded.isEmpty()){
        int t = discarded.findAndRemoveFromBook(a);
        if(t){
            //Book removed
        }
        else
        {
            printf("[removeFromDiscarded]: Failed to find the book to remove : value of t = %d , a = %lld \n", t, a);
        }
    }
}

void Register::logPrintTrac(){
    printf ("\n       .............\n");
    for(auto i: trac){
        printf("        %lld    %x\n", i.address, i.flag);
    }
    printf ("       .............\n\n");
}