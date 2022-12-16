#ifndef _VARYVEC_H_
#define _VARYVEC_H_

#include <stdlib.h>
#include <stdio.h>

#define _VARY_VEC_START_SIZE 8

// this can be defined here or included from another file
typedef struct Example {
  int num;
  char* str;
} Example;

// Replace "Example*" with whatever type you want
typedef Example* T;

typedef struct VaryVec {
  T* items;
  unsigned int _size;
  unsigned int _len;

  T (*get)(struct VaryVec, unsigned int i);
  T (*pop)(struct VaryVec*);
  void (*push)(struct VaryVec*, T item);
  void (*map)(struct VaryVec*, T (*fn)(T));
  void (*fdisplay)(struct VaryVec, FILE* out);
  void (*free)(struct VaryVec*);

  // this function will be called whenever an item
  // is deleted from the vector
  void (*ondelete)(void* item);

  // removed functionality to minimize the amount
  // of function pointers the vec needs to store: 
  // void (*len)(struct VaryVec);
  // void (*display)(struct VaryVec);
} VaryVec;

VaryVec* new_varyvec();
#endif
