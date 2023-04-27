#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// include the header files with the declarations of listset
#include "listset.h"

// create a new, empty linked list set
struct listset * listset_new() {
  struct listset * header;
  header = malloc(sizeof(struct listset));
  header -> head = NULL;
  return header;
}

/* check to see if an item is in the set
   returns 1 if in the set, 0 if not */
int listset_lookup(struct listset * this, char * item) {
  if(this -> head == NULL)
  {
    return 0;
  }
  else{
    for(struct listnode * lookup = this -> head; lookup -> next != NULL; lookup = lookup -> next)
    {
      if ( strcmp(lookup -> str, item) == 0) {
        return 1;
      }
    }
    return 0;
  }

}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set.
// New items that are not already in the set should                                  
// be added to the start of the list
void listset_add(struct listset * this, char * item) {
  struct listnode * insertnode;
  insertnode -> str = item;
  if(this -> head == NULL)
  {
    insertnode -> next = NULL;
    this -> head = insertnode;
  }
  else{
    for(struct listnode * currentnode = this -> head; currentnode != NULL; currentnode = currentnode -> next)
    {
      if(strcmp(currentnode -> str, item) == 0)
      {
        return;
      }
      else if(currentnode -> next == NULL)
      {
        currentnode -> next = insertnode;
      }
    }
  }
}

// remove an item with number 'item' from the set
void listset_remove(struct listset * this, char * item) {
  struct listnode * current;
  struct listnode * prev;
  if(this -> head == NULL){
    return;
  }else if(strcmp(this -> head -> str, item) == 0){
    current = this -> head;
    this -> head = current -> next;
    free(current);
    return;
  } else {
    for (prev = this -> head, current = prev -> next; current != NULL; prev = prev -> next, current = current -> next){
      if(strcmp(current -> str, item) == 0){
        prev -> next = current -> next;
        free(current);
        return;
      }
    }
  }
}

// place the union of src1 and src2 into dest
void listset_union(struct listset * dest, struct listset * src1,
                   struct listset * src2) {
         for(struct listnode * currentnode = src1 -> head; currentnode != NULL; currentnode = currentnode -> next)
         {
           listset_add(dest, currentnode -> str);
         }
         for(struct listnode * currentnode = src2 -> head; currentnode != NULL; currentnode = currentnode -> next)
         {
           listset_add(dest, currentnode -> str);
         }
}

// place the intersection of src1 and src2 into dest
void listset_intersect(struct listset * dest, struct listset * src1,
                       struct listset * src2) {
         for(struct listnode * iteratenode = src1 -> head; iteratenode != NULL; iteratenode = iteratenode -> next)
         {
           for(struct listnode * comparenode = src2 -> head; comparenode != NULL; comparenode = comparenode -> next){
             if(strcmp(iteratenode -> str, comparenode -> str) == 0)
             {
               listset_add(dest, iteratenode -> str);
             }
           }
         }
}

// return the number of items in the listset
int listset_cardinality(struct listset * this) {
  int cardinality = 0;
  for(struct listnode * currentnode = this -> head; currentnode != NULL; currentnode = currentnode -> next)
  {
    cardinality++;
  }
  return cardinality;
}

// print the elements of the list set
void listset_print(struct listset * this) {
  struct listnode * p;

  for ( p = this->head; p != NULL; p = p->next ) {
    printf("%s, ", p->str);
  }
  printf("\n");
}