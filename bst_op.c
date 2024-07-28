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


void delete_BST(int ele, struct node** root) {
    struct node* parent = NULL;
    struct node* current = *root;

    // Find the node to delete and its parent
    while (current != NULL && current->key != ele) {
        parent = current;
        if (ele < current->key)
            current = current->left;
        else
            current = current->right;
    }

    if (current == NULL) {
        // Node not found
        return;
    }

    // Case 1: Node to be deleted has no children
    if (current->left == NULL && current->right == NULL) {
        if (parent == NULL) {
            // Node to be deleted is root
            *root = NULL;
        } else if (parent->left == current) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
        free(current);
    }
    // Case 2: Node to be deleted has only one child
    else if (current->left == NULL) {
        if (parent == NULL) {
            *root = current->right;
        } else if (parent->left == current) {
            parent->left = current->right;
        } else {
            parent->right = current->right;
        }
        free(current);
    } else if (current->right == NULL) {
        if (parent == NULL) {
            *root = current->left;
        } else if (parent->left == current) {
            parent->left = current->left;
        } else {
            parent->right = current->left;
        }
        free(current);
    }
    // Case 3: Node to be deleted has two children
    else {
        // Find in-order successor
        struct node* successor_parent = current;
        struct node* successor = current->right;
        while (successor->left != NULL) {
            successor_parent = successor;
            successor = successor->left;
        }

        // Copy the value of the in-order successor to the current node
        current->key = successor->key;

        // Delete the in-order successor node
        if (successor_parent == current)
            successor_parent->right = successor->right;
        else
            successor_parent->left = successor->right;

        free(successor);
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