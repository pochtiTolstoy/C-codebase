#ifndef BIN_TREE_
#define BIN_TREE_

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

/*
static const int MAX_SIZE_TREE = 1000000;
static const int MAX_NUM_DUPLICATES = 1000000;
*/


/* INFO:
 * Binary search tree.
 * Working with int values.
 * Without balance.
 * Duplicates are counted inside node
 */

/* TODO:
 * delete node
 * delete key
 * non recursive traverse
 * sort array
 * add nodes limits
 * add size
 */

typedef struct Node {
  struct Node* left_;
  struct Node* right_;
  struct Node* parent_;
  int key_;
  int quantity_;
} Node;

typedef struct Bin_tree {
  struct Node* root_; 
  int num_nodes_;
} Bin_tree;

typedef Bin_tree BST;

void init_bst(BST*);
Node* insert_key(BST*, int);
void delete_node(BST*, Node*);
Node* find_key(BST*, int);
Node* get_min(Node*);
Node* get_max(Node*);
int size(BST*);

/* upper_bound
 * Search first element that is greater than i
 */
Node* upper_bound(Node*);

Node* lower_bound(Node*);
void traverse_inorder(BST*, void (*)(Node*));
void traverse_postorder(BST*, void (*)(Node*));

/* free_node
 * Do not care about tree structure!
 */
void delete_bst(BST*);
void print_node(Node*);
void print_key(Node*);
void print_bst_nodes(BST*);
void print_bst(BST*);


#endif /* BIN_TREE_ */
