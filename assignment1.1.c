#include <stdio.h>
#include <stdlib.h>

struct present {  
char *present_name;  
float price;  
};  
 
struct present* delete_present_list(struct present* present_list[], int num) {

   int i;
   //check if NUll
   if(present_list == NULL){

   return NULL;

   }
   //Loop through array
   for(i = 0; i < num; i++){

      free(present_list[i]);

   }

   free(present_list);

   return NULL; 
}

