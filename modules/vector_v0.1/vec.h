#ifndef VEC_H_
#define VEC_H_

#define REALLOC_COEF 2

#include <stddef.h>

typedef struct Pair {
  const char* key;
  size_t value;
} Pair;

typedef struct Vec {
  Pair* data; 
  size_t size;
  size_t capacity;
} Vec;

void init_vec(Vec*, size_t);
void delete_vec(Vec*);
void append_vec(Vec*, Pair);

#endif /* VEC_H_ */
