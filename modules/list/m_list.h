// list module
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
	Node* rear_;
  int size_;
} List;

// Help static methods
/*
static void check_node_alloc(const Node*);
static void check_node_number(const List*);
static void check_rear_correctness(const List*);
static void check_rear_pointer(const List*); 
static void inc_size(List*);
static void dec_size(List*);
static void check_clear_method(const List*);
static void check_pop(const List*);
*/

// General methods
void init_list(List*);

void push(List*, int);

int pop(List*);

// for immitating queue
void enqueue(List*, int);
int dequeue(List*);

// deallocating elements in list without head and tail.
void clear_list(List*);

/* free_list
 *
 * all elements are deallocated including head and tail.
 * list pointer itself is not NULL.
 */
void free_list(List*);

/* movenexttofront
 *
 * Moves next node after given to the front of the list.
 * Abort if given node is not in list
 * No changes if given node is last node in list including tail
 * Sets rear_ pointer correctly
 */ 
void movenexttofront(List*, const Node*);


// User methods
void print_list(const List*);


bool is_list_ready(const List*);

bool is_list_empty(const List*);

bool is_list_full(const List*);

/* find_node
 * Finds node in list and return non-constant pointer to this node.
 * NULL if given node is not in the list
 */
Node* find_node(const List*, const Node*);

/* find_node_ht
 * Finds node in list and return non-constant pointer to this node,
 * including head and tail.
 * NULL if given node is not in the list
 */
Node* find_node_ht(const List*, const Node*);

/* find_key
 * Finds first node with given key in list 
 * and return non-constant pointer to this node.
 * NULL if given node is not in the list
 */
Node* find_key(const List*, int);

/* find_key_ht
 * Finds first node with given key in list 
 * and return non-constant pointer to this node,
 * including head and tail.
 * NULL if given node is not in the list
 */
Node* find_key_ht(const List*, int);

int get_list_capacity(void);

int get_list_size(const List*);


#endif /* LIST_H_ */
