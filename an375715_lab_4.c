#include <stdio.h>
#include <stdlib.h>
typedef struct node {
char letter;
struct node* next;
} node;
// Returns number of nodes in the linkedList.
int length(node* head){
    int i = 0; 

    struct node* current = head; 

    while(head != NULL){
        i++;
        head = head->next; 
   }
    return i; 
}
// parses the string in the linkedList
//  if the linked list is head -> |a|->|b|->|c|
//  then toCString function wil return "abc"
char* toCString(node* head)
{   
    struct node* current = head; 

    int counted = length(head); 

    char* compiled = (char*) malloc( counted + 1 );

    current = head; 
    int i = 0; 

    while (current != NULL){
        compiled[i++] = current->letter; 
        current = current->next; 
    }
    compiled[counted] = '\0';

    return compiled; 
}
// inserts character to the linkedlist
// f the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as foolows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node** pHead, char c)
{
    struct node* temp = (struct node*) malloc(sizeof(struct node));
    temp->letter = c; 
    temp->next = NULL; 

    if (*pHead == NULL) {

        *pHead = temp; 

    }
    else{

        struct node* current = *pHead;

        while (current->next !=NULL){

            current = current->next;
        }

        current->next = temp; 
    }
}
// deletes all nodes in the linkedList.
void deleteList(node** pHead)
{
    node* current = *pHead; 
    while( current != NULL ){
        node* temp = current; 
        current = current->next;
        free(temp); 
    }
    *pHead = NULL; 
}
int main(void)
{
    int i, strLen, numInputs;
    node* head = NULL;
    char* str;
    char c;
    FILE* inFile = fopen("input.txt","r");
    fscanf(inFile, " %d\n", &numInputs);
    while (numInputs-- > 0){

    fscanf(inFile, " %d\n", &strLen);

    for (i = 0; i < strLen; i++){
        fscanf(inFile," %c", &c);
        insertChar(&head, c);
    }

    str = toCString(head);

    printf("String is : %s\n", str);

    free(str);

    deleteList(&head);

    if (head != NULL){

        printf("deleteList is not correct!");
        break;
    }
    }

    fclose(inFile);
    }