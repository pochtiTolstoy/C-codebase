#ifndef LIST_GEN_
#define LIST_GEN_

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>

static const int MAX_SIZE_LIST = 1000000;

typedef unsigned int ui;

typedef enum {
	DECIMAL_ELEM,
	REAL_ELEM,
	STRING_ELEM,
  PAIR_ELEM,
  VOID_ELEM
} vtype_list_t;

typedef enum {
	PDECIMAL,
	PREAL,
	PSTRING,
} vtype_pair_t;

typedef union {
  int64_t decimal;
  double  real;
  char*   string;
} value_pair_t;

typedef struct Pair {
  vtype_pair_t key_type_;
  vtype_pair_t value_type_;
  value_pair_t key;
  value_pair_t value;
} Pair;

typedef union {
	int64_t decimal;
	double  real;
	char*   string;
  Pair    pair;
  void*   void_t;
} value_list_t;

typedef struct Node {
	value_list_t key_;
	struct Node* next_;
} Node;

typedef struct List {
	Node* head_;	
	Node* tail_;
	Node* rear_;
	ui size_;
	vtype_list_t type_;
} List;

typedef bool (*Comparator) (value_list_t*, value_list_t*);

Node* init_list(List*, const char*);

Node* push(List*, ...);

void print_list(const List*);

void clear_list(List*);

void free_list(List*);

value_list_t pop(List*);

Node* find_node(const List*, const Node*);

Node* find_key(const List* list, ...);

void init_pair(Pair* pair, const char* format, ...);

#endif /* LIST_GEN_ */
