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
        struct entry *node = (struct entry*) malloc(sizeof(struct entry));
        node->Address = a;
        node->miniAddress = ma;
        node->next = NULL;

        e = node;
    }
    else{
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

void Queue::remove(){
    if(e == NULL){
        return;
    }
    else{
        struct entry *head = e;
        struct entry *second = (e)->next;
        e = second;
        free(head); // removing deleted one
    }
}

entry* Queue::old(){
    if(e == NULL){
        return NULL;
    }
    else{
        struct entry *head = e;
        printf("%lld ",head->Address);
        printf("%d\n",head->miniAddress);
        return head;
    }
}

void Queue::touch(int ma){
    if(e == NULL || e->next == NULL){
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
    }
}
