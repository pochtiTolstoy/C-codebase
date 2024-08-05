#ifndef LIST_GEN_
#define LIST_GEN_

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>

static const int MAX_SIZE_LIST = 1000000;

typedef unsigned int ui;

typedef enum {
	DECIMAL_ELEM,
	REAL_ELEM,
	STRING_ELEM
} vtype_list_t;

typedef union {
	int64_t decimal;
	double real;
	uint8_t* string;
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

Node* init_list(List*, const uint8_t*);

Node* push(List*, ...);

void print_list(const List*);

void clear_list(List*);

void free_list(List*);

value_list_t pop(List*);

Node* find_node(const List*, const Node*);

#endif /* LIST_GEN_ */
