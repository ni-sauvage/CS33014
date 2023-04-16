//
// CSU33014 Suplemental 2020 Additional Assignment
// Part B of a two-part assignment
//
// Please write your solution in this file

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "csu33014-annual-q2-code.h"


// Create an array of boolean values, such that for each element of
// list_a there is a corresponding boolean value. Each boolean value
// should be true if the corresponding element of list_a can also
// be found in list_b. Otherwise it should be false
bool * find_duplicates_sequential(char ** list_a, int size_a,
				  char ** list_b, int size_b) {

  // create an array of booleans with an element for each of list_a
  bool * duplicates = malloc(sizeof(bool) * size_a);
  
  for ( int i = 0; i < size_a; i++ ) { // for each string in list_a
    int is_duplicate = 0;
    for ( int j = 0; j < size_b; j++ ) { // for each string in list_b
      if ( strcmp(list_a[i], list_b[j]) == 0 ) {
	// the two strings are equal; list_a[i] is in list_b
	is_duplicate = 1;
      }
    }
    duplicates[i] = is_duplicate;
  }
  // return the array of booleans marking duplicates
  return duplicates;
}



// PLEASE WRITE YOUR PARALLEL VERSION HERE
//
// Please write a description of your algorithm and parallelization
// strategy here. Please also describe the time complexity of your
// approach. Please feel free to upload a pdf with your description
// and/or pictures if you prefer.
//
//
//
//
//
//
// And write your parallel code here:
bool * find_duplicates_parallel(char ** list_a, int size_a,
				char ** list_b, int size_b) {
  bool * result;
  
  // PLEASE REPLACE THE FOLLOWING CALL WITH YOUR PARALLEL CODE
  result = find_duplicates_sequential(list_a, size_a, list_b, size_b);
  
  return result;
}




