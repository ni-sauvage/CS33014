//
// CSU33014 Suplemental 2020 Additional Assignment
// Part B of a two-part assignment
//
// Please write your solution in this file

#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>
#include <omp.h>
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

int int_compare(const void * ptr2num1, const void * ptr2num2)
{
  int * fpnum1 = (int*) ptr2num1;
  int * fpnum2 = (int*) ptr2num2;
  int num1 = *fpnum1;
  int num2 = *fpnum2;

  if ( num1 > num2 )
    return 1;
  else if ( num1 < num2 )
    return -1;
  else
    return 0;
}

bool * find_duplicates_parallel(char ** list_a, int size_a, char ** list_b, int size_b) {
  bool * duplicates = malloc(sizeof(bool) * size_a);
  int * int_b = malloc(sizeof(int) * size_b);
  int * int_a = malloc(sizeof(int) * size_a);
  for(int i = 0; i < size_b; i++){
    int_b[i] = *(int *) list_b[i];
  }
  for(int i = 0; i < size_a; i++){
    int_a[i] = *(int *) list_a[i];
  }
  qsort(int_b, size_b, sizeof(int), int_compare);
  #pragma omp parallel for simd
  for ( int i = 0; i < size_a; i++ ) { // for each string in list_a
    duplicates[i] = bsearch(int_a+i, int_b, size_b, sizeof(int), int_compare)==NULL ? 0 : 1;
  }
  return duplicates;
}
