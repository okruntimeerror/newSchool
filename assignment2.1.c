#include <stdio.h> 
#include <stdlib.h>
 
typedef struct node {  
 int data;  
 struct node* next;  
} node;  
 
void insertAfterN(node* head) {  
   int true = 1;

   while (true) {

      node *t;
      node *temp; 

      temp=(node*) malloc( sizeof(node)); 
      temp->data=200; 
      temp->next=NULL; 
      
      if(head->data == 6 ){
        
         temp->next = head->next; 
         head->next = temp; 
        
      }

      head = head->next;

      if(head == NULL){

      break; 

     } 

   }
   
   
} 
 
void deallocateList(node** head) 
{ 
 node* tmp = *head; 
  
 while (tmp != NULL) 
 { 
  *head = tmp->next; 
  free(tmp); 
  tmp = *head; 
 } 
  
 *head = NULL; 
} 
 
int insertList(node** head, int data) 
{ 
 node* newNode = (node*) malloc(sizeof(node)); 
  
 if (newNode == NULL) 
  return -1; 
  
 newNode->data = data; 
 newNode->next = NULL; 
  
 newNode->next = *head; 
 *head = newNode; 
  
 return 1; 
} 
 
 
void printList(node* head) 
{ 
 node* tmp = head; 
  
 while (tmp != NULL) 
 { 
  printf("%d",tmp->data); 
  if (tmp->next != NULL) 
  { 
   printf(", "); 
  } 
  else 
  { 
   printf(".\n"); 
  } 
  tmp = tmp->next; 
 } 
} 

 
int main(void) 
{ 
 node* head = NULL; 
  
 insertList(&head, 5); 
 insertList(&head, 6); 
 insertList(&head, 6); 
 insertList(&head, 4); 
 insertList(&head, 6); 
 insertList(&head, 3); 
  
 printf("Initial List:\n"); 
 printList(head); 
 insertAfterN(head); 
 printf("Marked List:\n"); 
 printList(head); 
  
 deallocateList(&head); 
}