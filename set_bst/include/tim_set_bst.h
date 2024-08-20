#ifndef SET_BST_
#define SET_BST_

#include "tim_bin_tree.h"

typedef struct SET_BST {
	BST tree_;
} SET_BST;

typedef SET_BST Set;

void init_set(Set*);
void set_insert(Set*, int);
void set_remove(Set*, int);
bool set_contains(Set*, int);
int set_size(Set*);
bool set_is_empty(Set*);

// iterator it = begin(&set);
// it->key_;
typedef Node* iterator;
Node* set_begin(Set*);
Node* set_next(Node*);
void print_set(Set*);
int set_get_min(Set*);
int set_get_max(Set*);
Node* set_find(Set*, int);

void clear_set(Set*);

#endif /* SET_BST */
