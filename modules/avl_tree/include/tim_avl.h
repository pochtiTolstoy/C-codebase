#ifndef AVL_TREE_
#define AVL_TREE_

#include <stdio.h>
#include <stdbool.h>

/* TODO: delete_key, find_key, get_min, get_max 
 *       upper_bound, lower_bound, size 
 */

typedef unsigned int u32;

typedef struct Node {
  struct Node* left_; 
  struct Node* right_;
  struct Node* parent_;
  int key_;
  u32 num_key_;
  u32 height_;
} Node;

typedef struct avl_tree {
  Node* root_;
  u32 num_node_;
} AVL;

void init_avl(AVL*);
Node* insert_key(AVL*, int);
// bool is_avl_valid(AVL*);

u32 get_height(const Node*);

void traverse_inorder  (AVL*, void (*)(Node*));
void traverse_postorder(AVL*, void (*)(Node*));

void delete_avl(AVL*);
void print_avl_nodes(AVL*);
void print_avl(AVL*);
void print_node(Node*);
void print_key(Node*);

#endif /* AVL_TREE_ */
