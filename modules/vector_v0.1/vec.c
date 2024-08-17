#include <stdio.h>
#include <stdlib.h>
#include "vec.h"

static int check_alloc_(void* pt)
{
  if (NULL == pt) {
    fprintf(stderr, "Error: bad allocation.\n");
    return -1;
  }
  return 0;
}

static int realloc_vec_(Vec* vec) 
{
  if (vec == NULL || vec->data == NULL) return -1;
  Pair* new_data = NULL;
  size_t new_cap = vec->capacity * REALLOC_COEF;

  if (new_cap <= 0) {
    fprintf(stderr, "Error: \"size_t capacity\" field overflow, "
                    "during vector reallocation.\n");
    return -1;
  }

  new_data = malloc(sizeof(Pair) * new_cap); 
  if (check_alloc_(new_data) < 0) return -1;
  for (size_t idx = 0; idx < vec->size; ++idx)
    new_data[idx] = vec->data[idx];
  free(vec->data);
  vec->data = new_data;
  vec->capacity = new_cap;

  return 0;
}

void init_vec(Vec* vec, size_t cap) 
{
  if (vec == NULL || cap <= 0) return;
  vec->size = 0;
  vec->capacity = cap;
  vec->data = malloc(sizeof(Pair) * cap);
  if (check_alloc_(vec->data) < 0) exit(-1);
}

void delete_vec(Vec* vec)
{
  if (vec == NULL) return;
  if (vec->data != NULL)
    free(vec->data);
}

void append_vec(Vec* vec, Pair pair) 
{
  int realloc_res = 0;
  if (vec == NULL || vec->data == NULL) return;
  if (vec->size >= vec->capacity) 
    realloc_res = realloc_vec_(vec);
  if (realloc_res < 0) return;
  vec->data[vec->size++] = pair;
}
