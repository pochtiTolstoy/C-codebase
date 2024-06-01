// list module
#ifndef LIST_H_
#define LIST_H_

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

static const int MAX_SIZE_LIST = 100000;

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
static Node* swap_neighbours_next_(List*, Node*, Node*);
static void swap_neighbour_pointers_(Node*, Node*);
static void check_node_alloc(const Node*);
static void check_node_number(const List*);
static void check_rear_correctness(const List*);
static void check_rear_pointer(const List*); 
static void inc_size(List*);
static void dec_size(List*);
static void check_clear_method(const List*);
static void check_pop(const List*);
static void set_rear_pointer_(List*);
*/

// General methods
void init_list(List*);

Node* push(List*, int);

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
 * Safe, linear time
 *
 * Moves next node after given to the front of the list.
 * Returns NULL if given node is not in list.
 * No changes if given node is last node in list including tail.
 * If given node is head return NULL
 *
 * Sets rear_ pointer correctly
 * Returns Node from front of list
 */ 
Node* movenexttofront(List*, const Node*);

/* exchangenext
 * Safe, linear time
 *
 * Exchanges the positions of the nodes after the nodes pointed by u and v
 * Returns NULL if given nodes are not in list, if given nodes are equal or
 * if one of nodes is last element or tail
 *
 * Sets rear_ pointer correctly
 * Returns one of the exchanged node if everything ok
 */
Node* exchangenext(List*, const Node* u, const Node* v);

/* swap_neighbours
 * Safe, linear time
 *
 * Swaps two neighbour nodes in list after given pointers
 * Sets rear_ pointer correctly
 * Returns NULL if given nodes are not neigbours, 
 * Otherwise return one of the node.
 */
//Node* swap_neighbours_next(List*, Node* u, Node* v);

bool compare_lists(const List*, const List*);

List* sort_list(List*);

Node* get_prev_node(const List*, const Node*);

/* insertafter
 * Safe, linear time
 *
 * Inserts new node after given
 */
Node* insertafter(List*, const Node*, int);

Node* deletenext(List*, const Node*);

List* create_from_array(List*, int arr[], int size);

List* reverselist(List*);

// User methods
void print_list(const List*);

void print_node(const Node*);

bool is_list_ready(const List*);

bool is_list_empty(const List*);

bool is_list_full(const List*);

bool is_list_valid(const List*);

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

/* find_at
 * 
 * Find node by given index
 *
 */
Node* find_at(const List*, int);

int get_list_capacity(void);

int get_list_size(const List*);

// Code which should be in other files in future
void merge(int arr[], int, int, int);

void merge_sort(int arr[], int, int);

#endif /* LIST_H_ */
