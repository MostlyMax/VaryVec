#include "varyvec.h"

Example* timestwo(Example* a) {
  a->num *= 2;
  return a;
}

int main() {
  Example* t;

  VaryVec* vv = new_varyvec();

  // you can define the function that's called
  // whenever an item is deleted
  vv->ondelete = free;

  for (int i = 0; i < 1000; i++) {
    t = (Example*) malloc(sizeof(Example));
    t->num = i;
    // push and pop are usually O(1)
    vv->push(vv, t);
  }

  // make sure you free values (if necessary)
  // after popping them from the vector
  t = vv->pop(vv);
  free(t);

  vv->map(vv, timestwo);

  // dereferencing means this function call
  // will not mutate the vector
  vv->get(*vv, 1000);

  // make sure to free memory!
  // this will call the ondelete function
  // for each value remaining in the vector
  vv->free(vv);
}
