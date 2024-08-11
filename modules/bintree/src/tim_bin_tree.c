#include "../include/tim_bin_tree.h"

static void check_node_alloc_(Node* node) {
	if (NULL == node) {
		fprintf(stderr, "%s\n", "Tree bad allocation. Abort.\n");
		abort();
	}
}

static void traverse_inorder_(Node* node, void (*predicate)(Node*)) {
  if (node == NULL) return;
  traverse_inorder_(node->left_, predicate);
  (*predicate)(node);
  traverse_inorder_(node->right_, predicate);
}

static void traverse_postorder_(Node* node, void (*predicate)(Node*)) {
  if (node == NULL) return;
  traverse_postorder_(node->left_, predicate);
  traverse_postorder_(node->right_, predicate);
  (*predicate)(node);
}

// unsafe
static void transplant_(BST* tree, Node* u, Node* v) {
  if (u->parent_ == NULL)
    tree->root_ = v;
  else if (u == u->parent_->left_)
    u->parent_->left_ = v;
  else
    u->parent_->right_ = v;
  if (v != NULL)
    v->parent_ = u->parent_;
}

static void free_node_(Node* node) {
  if (node == NULL) return;
  free(node);
}

void init_bst(BST* tree) {
  tree->root_ = NULL;
  tree->num_nodes_ = 0;
}

Node* insert_key(BST* tree, int key) {
  if (tree == NULL) return NULL;
  Node* prev_node = NULL; 
  Node* walk_node = tree->root_;
  while (walk_node != NULL) {
    if (key == walk_node->key_) {
      assert(walk_node->quantity_ > 0); 
      ++walk_node->quantity_;
      return walk_node;
    }
    prev_node = walk_node;
    walk_node = (key < walk_node->key_) 
        ? walk_node->left_ 
        : walk_node->right_;
  }
  Node* new_node = (Node*) malloc(sizeof(Node));
  check_node_alloc_(new_node);
  ++tree->num_nodes_;
  new_node->left_ = NULL;
  new_node->right_ = NULL;
  new_node->key_ = key;
  new_node->quantity_ = 1;
  new_node->parent_ = prev_node;
  if (prev_node == NULL) 
    tree->root_ = new_node;
  else if (new_node->key_ < prev_node->key_) 
    prev_node->left_ = new_node;
  else
    prev_node->right_ = new_node;
  return new_node;
}

void delete_node(BST* tree, Node* del_node) {
  if (del_node->left_ == NULL) {
    transplant_(tree, del_node, del_node->right_);
    return free(del_node);
  }
  if (del_node->right_ == NULL) {
    transplant_(tree, del_node, del_node->left_);
    return free(del_node);
  }
  Node* rotate_node = get_min(del_node->right_);
  if (rotate_node->parent_ != del_node) {
    transplant_(tree, rotate_node, rotate_node->right_);
    rotate_node->right_ = del_node->right_;
    rotate_node->right_->parent_ = rotate_node;
  }
  transplant_(tree, del_node, rotate_node);
  rotate_node->left_ = del_node->left_;
  rotate_node->left_->parent_ = rotate_node;
  free(del_node);

  --tree->num_nodes_;
}

Node* find_key(BST* tree, int key) {
  if (tree == NULL) return NULL;
  Node* walk_node = tree->root_;
  while (walk_node != NULL && key != walk_node->key_)
    walk_node = (key < walk_node->key_) 
              ? walk_node->left_ 
              : walk_node->right_;
  return walk_node;
}

Node* get_min(Node* node) {
  if (node == NULL) return NULL;
  while (node->left_ != NULL) 
    node = node->left_;
  return node;
}

Node* get_max(Node* node) {
  if (node == NULL) return NULL;
  while (node->right_ != NULL)
    node = node->right_;
  return node;
}

int size(BST* tree) {
  if (tree == NULL) {
    fprintf(stderr, "Method size(int) error: Null tree\nAbort.\n");
    abort();
  }
  return tree->num_nodes_;
}

Node* upper_bound(Node* node) {
  if (node == NULL) return NULL;
  if (node->right_ != NULL)
    return get_min(node->right_);
  Node* prev_node = node->parent_;
  while (prev_node != NULL && node == prev_node->right_) {
    node = prev_node; 
    prev_node = prev_node->parent_;
  }
  return prev_node;
}

Node* lower_bound(Node* node) {
  if (node == NULL) return NULL;
  if (node->left_ != NULL)
    return get_max(node->left_);
  Node* prev_node = node->parent_;
  while (prev_node != NULL && node == prev_node->left_) {
    node = prev_node;
    prev_node = prev_node->parent_;
  }
  return prev_node; 
}

// Runs through tree
void traverse_inorder(BST* tree, void (*predicate)(Node*)) {
  if (tree == NULL) return;
  traverse_inorder_(tree->root_, predicate);
}

void traverse_postorder(BST* tree, void (*predicate)(Node*)) {
  if (tree == NULL) return;
  traverse_postorder_(tree->root_, predicate);
}

void delete_bst(BST* tree) {
  traverse_postorder(tree, free_node_);
  tree->root_ = NULL;
  tree->num_nodes_ = 0;
}

void print_bst_nodes(BST* tree) {
  traverse_inorder(tree, print_node);
}

void print_bst(BST* tree) {
  traverse_inorder(tree, print_key);
  putchar('\n');
}

// Simple helper functions, working with single node
void print_node(Node* node) {
  if (node == NULL) return;
  printf("Node:       %p.\n", node);
  printf("--key:      %d,\n", node->key_);
  printf("--quantity: %d,\n", node->quantity_);
  putchar('\n');
}

void print_key(Node* node) {
  if (node == NULL) return;
  printf("%d ", node->key_);
}
