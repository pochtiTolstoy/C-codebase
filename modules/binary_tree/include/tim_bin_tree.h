#ifndef BIN_TREE_
#define BIN_TREE_

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

static const int MAX_SIZE_TREE = 1000000;
static const int MAX_NUM_DUPLICATES = 1000000;


/* INFO:
 * Binary search tree.
 * Working with int values.
 * Without balance.
 * Duplicates are counted inside node
 */

/* TODO:
 * DO: insert      - get key and allocate new node in binary tree
 * DO: delete      - clears all tree
 * search      - find by key, find by node
 * minimum     - return minimal element in tree
 * maximum     - return minimal element in tree
 * lowerbound  - maximum element in tree less than the given key
 * upperbound  - minimum element in tree greater than the given key
 * delete_node - delete node with all duplicates and change struct of tree.
 * delete_key  - reduces the number in a node if there are duplicates
 *               otherwise calls delete_node
 * DO: print_tree  - prints tree using inorder tree walk
 */

/* Static methods:
 * check_node_alloc_  - check bad alloc
 * traverse_inorder_  - work with nodes, not a tree root.
 * free_node_ - calls free on given node
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
} Bin_tree;

typedef Bin_tree BST;

void init_bst(BST*);
Node* insert_key(BST*, int);
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
