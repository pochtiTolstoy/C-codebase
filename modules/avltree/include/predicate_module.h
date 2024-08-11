#ifndef PREDICATE_MODULE
#define PREDICATE_MODULE

#include "tim_avl.h"

typedef unsigned int u32;
typedef struct Node Node;
typedef struct predicate_module predmodule;
typedef void (*predfunc)(Node*, predmodule*);
typedef void (*predfunc_simple)(Node*);
/*
typedef void (*predicate_read)(const Node*);
typedef void (*predicate_write)(Node*);
typedef void (*predicate_accumulate)(Node*, void*);
typedef void (*predicate_store)(Node*, void**);
*/

typedef enum predicate_state {
  READ, 
  WRITE, 
  ACCUMULATE, 
  STORE, 
  COMPARE,
  SIMPLE,
  UNDEFINED
} predstate;

typedef struct storage_data {
  void* storage_begin;
  void* storage_current; /* can be incremented */
  void* storage_end;
} storage_data;

typedef struct cmp_data {
  bool equals;
} cmp_data;

typedef struct avl_data {
  bool valid;
  u32 nodes;
  u32 elems;
} avl_data;

typedef struct predicate_module {
  predstate state;   
  predfunc* pred;
  void* accumulator; 
  storage_data sd;
  cmp_data cd;
  avl_data* ad;
} predicate_module;


void init_predmod(predmodule*, predstate);
void set_predicate(predmodule*, void*);
void set_accumulator(predmodule*, void*);
void set_storage(predmodule*, void*, void*);
void init_avl_data(predmodule*);
void free_avl_data(predmodule*);

#endif /* PREDICATE_MODULE */
