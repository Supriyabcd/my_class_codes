#include <stdio.h>
#include <stdlib.h>

struct node
{
    int key;
    struct node* right;
    struct node* left;
};

struct node* insert_BST(struct node*, int);
struct node* search_BST(int, struct node*) ;
struct node* inorder_successor(struct node*, struct node *);
struct node* inorder_predecessor(struct node*, struct node *);
void delete_BST(int, struct node**);
void print_in_order(struct node*);
void print_level_order(struct node*);

int main()
{
    int n, c, ele;
    struct node *root = NULL;
    printf("Enter no. of elements: ");
    scanf("%d", &n);

    int seq[n];
    printf("Enter the elements: \n");
    for (int i = 0; i < n; i++)
        scanf("%d", &seq[i]);

    for (int i = 0; i < n; i++) {
        root = insert_BST(root, seq[i]);
    }
    
    printf("Enter the number for printing the BST using \n 1 - Insertion \n 2 - Searching \n 3 - Inorder successor \n 4 - Inorder predecessor\n 5 - Deletion \n "); 
    scanf("%d", &c);
    switch(c)
    {
      case 1: printf("Enter the element: ");
      	      scanf("%d",&ele);
      	      root = insert_BST(root, ele);
      	      print_level_order(root);
              break;
      case 2: printf("Enter the search element: ");
              scanf("%d",&ele);
              struct node* found  =  search_BST(ele,root); 
              if(found != NULL)
              {
               printf(" Yes ");
              }
              else{
              printf(" No ");
              }
              break;
      case 4: printf("Enter the element: ");
      	      scanf("%d",&ele);
              found = search_BST(ele, root);
      
              if(found != NULL)
             {
               struct node *p = inorder_predecessor(root, found);
                 if (p != NULL)  
                     printf("The inorder predecessor is %d", p->key );
                 else
                   printf("No inorder predecessor"); 
              } else {
               printf("Element not found");
              } 
              break;
      case 3: printf("Enter the element:");
              scanf("%d",&ele);
              found = search_BST(ele, root);
      
              if(found != NULL)
             {
               struct node *s = inorder_successor(root, found);
                 if (s != NULL)  
                     printf("The inorder successor is %d", s->key );
                 else
                   printf("No inorder successor"); 
              } else {
               printf("Element not found");
              } 
              break;
      case 5: printf("Enter the element:");
              scanf("%d",&ele);
              delete_BST(ele, &root);
              break;
      default:printf("invalid choice");
              break;

     }
    return 0;
}

struct node* insert_BST(struct node* r, int value)
{
    if (r == NULL)
    {
        struct node* new_node = (struct node*)malloc(sizeof(struct node));
        new_node->key = value;
        new_node->left = NULL;
        new_node->right = NULL;
        return new_node;
    }

    if (value < r->key)
    {
        r->left = insert_BST(r->left, value);
    }
    else if (value > r->key)
    {
        r->right = insert_BST(r->right, value);
    }

    return r;
}

struct node* search_BST(int ele, struct node* root)
{
 if(root == NULL || root->key == ele )
    return root;
 else{
    if(ele < root->key )
     return search_BST(ele, root->left);   
    else
      return search_BST(ele, root->right);
 } 	  
}
    
struct node* inorder_successor(struct node *root, struct node *n)    
{

 struct node *suc = NULL;
 if (n == NULL)
   return NULL;
   
 if(n->right != NULL){
    n = n->right;
    while(n->left != NULL)
       n = n->left;   
      return n; 
 } 
  
  while (root != NULL)
  {
        if (n->key < root->key)
        {
            suc = root;
            root = root->left;
        }
        else if (n->key > root->key)
        {
            root = root->right;
        }
        else
        {
            break;
        }
    }

    return suc;
}    


struct node* inorder_predecessor(struct node *root, struct node  *n )
{
 if (n == NULL)
   return NULL;
   
 if(n->left != NULL){
    n = n->left;
    while(n->right != NULL)
       n = n->right;
    return n;   
 } 
  struct node *pred = NULL;
  while (root != NULL)
  {
        if (n->key < root->key)
        {
            root = root->left;
        }
        else if (n->key > root->key)
        {
            pred = root;
            root = root->right;
        }
        else
        {
            break;
        }
    }
    return pred;
}

void delete_BST(int ele, struct node** root)
{
    struct node* found = search_BST( ele, *root);
 if(found != NULL)
{
  if(found->right == NULL && found->left == NULL)
    found = NULL;
  else 
  if(found->right == NULL)
  {
   found->key = (found->left)->key;
   found-> left = NULL;
  }
  else 
   if(found->left == NULL)
  {
   found->key = (found->right)->key;
   found-> right = NULL;
  }
  else {
  struct node *s = inorder_successor(*root, found);
  if(s != NULL){
  found->key = s->key;
  delete_BST(s->key,root);
  } else{
  struct node *p = inorder_predecessor(*root, found);
  if(p != NULL)
  found->key = p->key;
  delete_BST(p->key,root);
 }
}
}
 print_level_order(*root);
    
}

void print_level_order(struct node* root)
{
 if (root == NULL)
        return;

    struct node* queue[100];
    int front = -1, rear = -1;

    queue[++rear] = root;

    while (front != rear)
    {
        struct node* current = queue[++front];
        printf("%d ", current->key);

        if (current->left != NULL)
            queue[++rear] = current->left;

        if (current->right != NULL)
            queue[++rear] = current->right;
    }
}  