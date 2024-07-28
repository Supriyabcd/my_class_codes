#include<stdio.h>
#include <stdlib.h>

void swap(int *x, int *y)
{
  int temp = *x;
  *x = *y ;
  *y = temp;
}

void heapify(int a[], int n, int i)
{
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;
  
  if (left < n && a[left] > a[largest])
      largest = left;
      
  if (right < n && a[right] > a[largest])
       largest = right;
          
   if (largest != i)
   {
   swap(&a[i], &a[largest]);
   heapify(a, n, largest);
   }
 }
 
void buildMaxHeap(int a[], int n)
{
  int startIndex = (n/2) - 1;
  
  for(int i =startIndex; i >= 0; i--){
     heapify(a, n, i);
 }
}
 
void printHeap(int a[], int n)
{
   printf("Heap elements: ");
   for (int i = 0; i < n; i++)
      printf("%d ", a[i]);
   printf("\n");
}
        
    
    
int main()
{
   int n;
   printf("Enter array size: ");
   scanf("%d", &n);
   
   int a[n];
   printf("Enter the elements: \n");
   for(int i = 0; i < n; i++)
       scanf("%d", &a[i]);
       
  buildMaxHeap(a,n);
  
  printf("Max Heap created .\n");
  printHeap(a,n);
  
  return 0;
}
    