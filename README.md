# Vary Vec
Another implementation of vectors in C. This one is a bit funny because it pretends to be OOP!

The vector type must be determined at compile time so it has to be defined manually (varied!) in "varyvec.h".

```
// this can be defined here or included from another file
typedef struct Example {
  int num;
  char* str;
} Example;

// Replace "Example*" with whatever type you want
typedef Example* T;

```

Vector is created by calling new_varyvec() -> returns a pointer to a VaryVec type.

You can use this pointer to call functions

```
VaryVec vv;
vv = new_varyvec();

vv->push(vv, 123);
// derefering is needed for functions that explicitly
// will not mutate the vector
vv->get(*vv, 0);
```

