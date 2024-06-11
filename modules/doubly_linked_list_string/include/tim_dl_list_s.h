#ifndef DLL_H_
#define DLL_H_

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

static const int MAX_SIZE_LIST = 100000;

typedef struct Node {
	struct Node* next_;
	struct Node* prev_;
	char* str_;
} Node;

typedef struct List {
	Node* head_;
	Node* tail_;
	int size_;
} List;

/* Static methods
static void check_node_alloc(const Node* node);
*/

void init_list(List*);

Node* push(List*, const char*);

void pop(List*);

char* pop_str(List*);

Node* insertafter_f(List*, Node*, const char*);

Node* find_str(List*, const char*);

Node* delete_node_f(List*, Node*);

void clear_list(List*);

void free_list(List*);

bool is_list_full(const List*);

bool is_list_empty(const List*);

void print_node(Node*);

void traverse(List*, void (*pf)(Node*));

void print_list(List*);

#endif /* DLL_H_ */
