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

void Queue::insert(addr_uint a, int ma){
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
        head->next = ein;
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
        //printf("Queue : old() | E is NULL\n");
        return NULL;
    }
    else{
        struct entry *head = e;
        //printf("" PRINTADD " ",head->Address);
        //printf("%d\n",head->miniAddress);
        return head;
    }
}

void Queue::touch(int ma){
    if(e == NULL && e->next == NULL){
        printf("ERROR: Blank Queue");
        return;
    }
    if(e->next == NULL){
        //No action required
        //printf("MSG: Single element Queue\n");
        return;
    }
    if(ma < 0 || ma > 63){
        printf("ERROR: Invalid Mini Address\n");
        return;
    }
    struct entry* tempe = e;
    while(tempe != NULL && tempe->next != NULL){
      if (tempe->miniAddress == ma){
        struct entry *node = (struct entry*) malloc(sizeof(entry));
        node->Address = tempe->Address;
        node->miniAddress = tempe->miniAddress;
        node->next = NULL;

        struct entry* head = tempe->next;
        tempe->Address = head->Address;
        tempe->miniAddress = head->miniAddress;
        tempe->next = head->next;

        free(head);

	      struct entry* second = tempe;
        while(second != NULL && second->next != NULL){
          second = second->next;
        }

        second->next = node;
        return;
      }
      tempe = tempe->next;
    }
    if(tempe != NULL || tempe->next != NULL){
      if(tempe->miniAddress == ma){
        //No action needed
        //printf("MSG: Mini Address is last in the queue\n");
        return;
      }else{
        printf("ERROR: Mini Address is missing in the queue\n");
      }
    }else{
      printf("ERROR: Mini Address is missing in the queue\n");
    }

}

int Queue::getMiniAddressFromQueue(addr_uint a){
    int m_ma = -1;
    struct entry* ea = e;
    while(ea != NULL){
        //printf(" getMiniAddressFromQueue Address in queue:  " PRINTADD " Address looking for: " PRINTADD "\n",ea->Address, a);
        if(ea->Address == a){
            m_ma = ea->miniAddress;
        }
        ea = ea->next;
    }
    return m_ma;
}
void Queue::clean(){
    while(remove() != -1){
        continue;
    }
}

void Queue::removeTail(){
    if(e == NULL){
        printf("Queue : removeTail() | Error : Queue empty\n");
        return;
    }
    entry* tempe = e;
    if(tempe->next==NULL){
        free(tempe);
        e = NULL;
        return;
    }
    while(tempe->next->next !=NULL){
        tempe = tempe->next;
    }
    entry* tempe2 = tempe->next;
    tempe->next = NULL;
    free(tempe2);
}

bool Queue::isEmpty(){
    if(e == NULL){
        return true;
    }
    else
        return false;
}
