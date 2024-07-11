#ifndef AVL_TREE_
#define AVL_TREE_

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "predicate_module.h"

/* 0 - to turn off auto balance */
#define AUTO_BALANCE_ 1

typedef unsigned int u32;
typedef struct Node Node;
typedef struct avl_tree AVL;

struct Node {
  Node* left_; 
  Node* right_;
  Node* parent_;
  int key_;
  u32 num_key_;
  u32 height_;
};

struct avl_tree {
  Node* root_;
  u32 num_node_;
};

void  init_avl(AVL*);
Node* insert_key(AVL*, int);
Node* delete_key(AVL*, int);
Node* find_key(AVL*, int);
void delete_avl(AVL*);
Node* get_min(Node*);
Node* get_max(Node*);

Node* create_avl_from_array(AVL*, int [], u32);
int*  create_arr_from_avl(AVL*);
bool cmp_avl(AVL*, AVL*);
bool cmp_avl_with_arr(AVL*, int[], u32);
bool cmp_avl_with_string(AVL*, const char*);
bool is_balanced(AVL*);
//bool is_avl_valid(AVL*);

u32 get_height(const Node*);

void print_avl_nodes(AVL*);
void print_avl(AVL*);
void print_root(AVL*);
void print_node(Node*);
void print_key(Node*);

bool is_avl_empty(AVL*);

u32 get_avl_num_elems(AVL*);
u32 get_avl_size(AVL*);

#endif /* AVL_TREE_ */
