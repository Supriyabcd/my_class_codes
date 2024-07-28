#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node *next;
};

void delete_before(struct node **h, int i){
   
  struct node *p, *q, *t;
   if( *h == NULL||(*h)->next == NULL)
      printf("underflow");
      
    if((*h)->data == i){
    printf("No element before first element");
    }  
      
    q = *h;
    p = (*h)->next;
    
    while(p->next != NULL && p->next->data != i){
       q = q->next; 
       p = p->next;
    }
    
    if(p->next != NULL){
       t = q->next;
       q->next = p->next;
       free(t);
    }else{
       printf("Element not found");   
    } 
}

int main(){
  struct node *head, *p, *q;
  int i = 1, n, x, element;
  
  printf("Input %d:",i);
  scanf("%d",&n);
  
  p =  (struct node*)malloc(sizeof(struct node));
  p->data = n;
  p->next = NULL;
  head = p;
  
  for(i=2; i<=5; i++){
  q = (struct node*)malloc(sizeof(struct node));
  printf("Input %d:",i);
  scanf("%d",&n);
  q->data = n;
  q->next = NULL;
  p->next = q;
  p = q;
  }
  printf("Enter element: ");
            scanf("%d",&element);
            delete_before(&head, element);
p = head;
  while( p != NULL)
  {
    printf("%d ",p->data);
    p = p->next;
  }
  return 0;
  
 }            
            
            