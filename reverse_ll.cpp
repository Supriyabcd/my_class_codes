// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node* next;
};

void reverse_list(struct node **head, struct node *p, struct node *h){
    if (h->next == NULL)
       *head = h;
    else {
       reverse_list(head,h,h->next);
       h->next = p;
    }  
}

int main() {
    struct node *head,*p,*q,*temp,*nextNode;
    p =(struct node*)malloc(sizeof(struct node));
    p->data = 9;
    p->next = NULL;
    head = p;

    p=(struct node*)malloc(sizeof(struct node));
    p->data = 4;
    p->next = NULL;
    head->next = p;
        
    q=(struct node*)malloc(sizeof(struct node));
    q->data = 3;
    q->next = NULL;
    p->next = q;
    p = q;
    
    while(q!=NULL){
        printf("%d",q->data);
        q = q->next;
    }
    reverse_list(&head,NULL,head);
    
    printf("\nReversed list:");
    temp = head;
    while(temp != NULL)
    {
       printf("%d ",temp->data);
       temp = temp->next;
    }
   
    temp = head;
    while(temp != NULL){
        nextNode = temp->next;
        free(temp);
        temp = nextNode;
    }
    return 0;
}