#ifndef LIST_H_
#define LIST_H_

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

typedef struct Node {
  int key_;
  struct Node* next_;
} Node;

typedef struct List {
  Node* head_;
  Node* tail_;
  int size_;
} List;

// General methods
void init_list(List*);
void push(List*, int);
int pop(List*);

// deallocating elements in list without head and tail.
void clear_list(List*);

// all elements are deallocated including head and tail.
// list pointer itself is not NULL.
void free_list(List*);

// User methods
void print_list(const List*);
bool is_list_ready(const List*);
bool is_list_empty(const List*);
bool is_list_full(const List*);
int get_list_capacity(void);
int get_list_size(const List*);

// Help static methods
static void check_node_alloc(const Node*);
static void check_node_number(const List*);
static void inc_size(List*);
static void dec_size(List*);
static void check_clear_method(const List*);
static void check_pop(const List*);

#endif /* LIST_H_ */
