#include "Queue.h"
#include <cstdlib>
#include <cstdio>

Queue::Queue(){
        /* struct entry *e = (struct entry*) malloc(sizeof(entry));
        e->Address = 0;
        e->miniAddress = 0;
        e->next = NULL;*/
        e = NULL;
}

void Queue::insert(long long int a, int ma){
    if(e == NULL){
        //printf("Hello Bug\n");
        struct entry *node = (struct entry*) malloc(sizeof(struct entry));
        node->Address = a;
        node->miniAddress = ma;
        node->next = NULL;

        e = node;
    }
    else{
        //printf("Hello Bug B\n");
        struct entry *node = (struct entry*) malloc(sizeof(struct entry));
        node->Address = a;
        node->miniAddress = ma;
        node->next = NULL;

        struct entry *head = e;
        while(head->next != NULL){
            head = head->next;    
        }
        head->next = node;        
    }
}
//insert using entry*
void Queue::insert(entry* ein){
    if(e == NULL){
        e = ein;
    }
    else{
        struct entry *head = e;
        while(head->next != NULL){
            head = head->next;    
        }
        head->next = e;
    }
}


int Queue::remove(){
    if(e == NULL){
        return 0; // shouldn't happen
    }
    else if( e->next == NULL){
        free(e);
        e = NULL;
        return -1; // destroy the queue
    }
    else{
        struct entry *head = e;
        struct entry *second = (e)->next;
        e = second;
        free(head); // removing deleted one
        return 1;
    }
}

entry* Queue::old(){
    //printf("Hello Bug C\n");
    if(e == NULL){
        return NULL;
    }
    else{
        struct entry *head = e;
        //printf("%lld ",head->Address);
        //printf("%d\n",head->miniAddress);
        return head;
    }
}

void Queue::touch(int ma){
    if(e == NULL || e->next == NULL){
        printf("ERROR: Blank Queue");
        return;
    }
    if(e->next == NULL){
        printf("MSG: Single element Queue\n");
        return;
    }
    if(ma < 0 || ma > 63){
        printf("ERROR: Invalid Mini Address\n");
        return;
    }
    else if (e->miniAddress == ma){
        struct entry *node = (struct entry*) malloc(sizeof(entry));
        node->Address = e->Address;
        node->miniAddress = e->miniAddress;
        node->next = NULL;
	
        struct entry* head = e;
	    e = e->next;
        free(head);

	    struct entry* second = e;
        while(second != NULL && second->next != NULL){
            second = second->next;
        }
	
        second->next = node;
        return;
    }else{
        struct entry* head = e;
        while(head->next->miniAddress == ma && head->next->next != NULL){
            head = head->next;
        }
        struct entry* second = head->next;
        head = head->next->next;
        while(head->next != NULL){
            head = head->next;
        }
        head->next=second;
        second->next=NULL;
        return;
    }
    printf("ERROR: Mini Address is missing in the queue\n");
}

int Queue::getMiniAddressFromQueue(long long int a){
    int m_ma = -1;
    struct entry* ea = e;
    while(ea != NULL){
        //printf(" getMiniAddressFromQueue Address in queue:  %lld Address looking for: %lld\n",ea->Address, a);
        if(ea->Address == a){
            m_ma = ea->miniAddress;
        }
        ea = ea->next;
    }
    return m_ma;
}

bool Queue::isEmpty(){
    if(e == NULL){
        return true;
    }
    else
        return false;
}