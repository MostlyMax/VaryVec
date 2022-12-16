#include "varyvec.h"

void _varyvec_push(VaryVec* vv, T item) {
  T* temp_vv;

  if (vv->_len >= vv->_size) {
    vv->_size *= 2;

    temp_vv = (T*) realloc(vv->items, sizeof(T) * vv->_size);
    if (temp_vv == NULL) {
      perror("failed to realloc during push");
      exit(-1);
    }
    
    vv->items = temp_vv;
  }

  vv->items[vv->_len] = item;
  vv->_len++;
}

T _varyvec_get(VaryVec vv, unsigned int i) {
  if (i >= vv._len) {
    fprintf(stderr, "Error: tried to access VaryVec at index %d when the last index is %d\n", i, vv._len - 1);
    exit(-1);
  }

  return vv.items[i];
}

T _varyvec_pop(VaryVec* vv) {
  vv->_len--;

  T item = vv->items[vv->_len];

  return item;  
}

void _varyvec_map(VaryVec* vv, T (*fn)(T)) {
  int i;
  for (i = 0; i < vv->_len; i++) {
    vv->items[i] = fn(vv->items[i]);
  }
}

void _varyvec_free(VaryVec* vv) {
  int i;
  for (i = 0; i < vv->_len; i++) {
    vv->ondelete(vv->items[i]);
  }
  free(vv->items);
  free(vv);
}

unsigned int _varyvec_len(VaryVec vv) {
  return vv._len;
}

char* _varyvec_T_into_chars(T t) {
  char* buf;
  unsigned int length;


  // Default behavior is to just print the address of the type.
  // this can easily be changed by setting the template string
  // and where t points
  length = snprintf(NULL, 0, "%p", t);
  buf    = (char*) malloc((length + 1) * sizeof(char));

  snprintf(buf, length + 1, "%p", t);

  return buf;
}

void _varyvec_fdisplay(VaryVec vv, FILE* out) {
  char* temp;
  int i;

  if (vv._len <= 0) {
    fprintf(out, "[]");
    return;
  }

  temp = _varyvec_T_into_chars(vv.items[0]);
  fprintf(out, "[%s", temp);
  free(temp);
  for (i = 1; i < vv._len; i++) {
    temp = _varyvec_T_into_chars(vv.items[i]);
    fprintf(out, ", %s", temp);
    free(temp);
  }
  fprintf(out, "]\n");
}

void _varyvec_display(VaryVec vv) {
  vv.fdisplay(vv, stdout);
}

void _varyvec_do_nothing(void* item) {};

VaryVec* new_varyvec() {
  VaryVec* vv = (VaryVec*) malloc(sizeof(VaryVec));

  vv->items = (T*) malloc(sizeof(T) * _VARY_VEC_START_SIZE);

  if (vv->items == NULL) {
    perror("Failed to malloc VaryVec");
    exit(-1);
  }

  vv->_len     = 0;
  vv->_size    = _VARY_VEC_START_SIZE;

  vv->push     = _varyvec_push;
  vv->get      = _varyvec_get;
  vv->pop      = _varyvec_pop;
  vv->map      = _varyvec_map;
  vv->fdisplay = _varyvec_fdisplay;
  vv->free     = _varyvec_free;

  vv->ondelete = _varyvec_do_nothing;

  return vv;  
}

