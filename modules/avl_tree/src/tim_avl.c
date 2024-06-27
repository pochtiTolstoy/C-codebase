#include "../include/tim_avl.h"

static u32 max_(u32 a, u32 b) {
  return (a < b) ? b : a;
}

static void check_node_alloc_(Node* node) {
  if (NULL == node) {
    fprintf(stderr, "%s\n", "Tree bad allocation. Abort.");
    abort();
  }
}

static void check_null_node_(const Node* node) {
  if (NULL == node) {
    fprintf(stderr, "%s\n", "Node is NULL. Abort.");
    abort();
  }
}

static void free_node_(Node* node) {
  if (NULL == node)  return;
  free(node);
}

static void traverse_inorder_(Node* node, void (*predicate)(Node*)) {
  if (NULL == node) return;
  traverse_inorder_(node->left_,  predicate);
  (*predicate)(node);
  traverse_inorder_(node->right_, predicate);
}

static void traverse_postorder_(Node* node, void (*predicate)(Node*)) {
  if (NULL == node) return;
  traverse_postorder_(node->left_,  predicate);
  traverse_postorder_(node->right_, predicate);
  (*predicate)(node);
}

static u32 get_balance_(const Node* node) {
  check_null_node_(node);
  return (get_height(node->left_) - get_height(node->right_));
}

static u32 get_recalc_height_(const Node* node) {
  check_null_node_(node);
#define THIS_NODE 1
  return THIS_NODE + max_(get_height(node->left_), get_height(node->right_));
}

/* turn x clockwise */
static Node* right_rotate_(Node* x) {
  Node *y, *z;

  /* check valid form */
  check_null_node_(x);
  if (NULL == x->left_) return x;

  y = x->left_;  /* save subtree */
  z = y->right_; /* save subtree */

  /* rotate */
  y->right_ = x;
  x->left_  = z;

  /* change parents */
  x->parent_ = y;
  y->parent_ = NULL; /* if y will become a root */
  if (NULL != z) z->parent_ = x;

  /* recalc height: x - first, y - second */
  x->height_ = get_recalc_height_(x);
  y->height_ = get_recalc_height_(y);

  return y;
}

/* turn x counter clockwise */
static Node* left_rotate_(Node* x) {
  Node *y, *z;

  /* check valid form */
  check_null_node_(x);
  if (NULL == x->right_) return x;

  y = x->right_; /* save subtree */
  z = y->left_;  /* save subtree */

  y->left_  = x;
  x->right_ = z;

  /* change parents */
  x->parent_ = y;
  y->parent_ = NULL; /* if y will become a root */
  if (NULL != z) z->parent_ = x;

  /* recalc height: x - first, y - second */
  x->height_ = get_recalc_height_(x);
  y->height_ = get_recalc_height_(y);

  return y;
}

static Node* create_node_(int key) {
  Node* new_node = (Node*) malloc(sizeof(Node));

  check_node_alloc_(new_node);

  new_node->left_    = NULL;
  new_node->right_   = NULL;
  new_node->parent_  = NULL;
  new_node->key_     = key;
  new_node->num_key_ = 1;
  new_node->height_  = 1;

  return new_node;
}

static Node* insert_key_(Node* node, int key, u32* num_node) {
  int node_balance;

  /* 1. Going down. 
   *
   * We will recursively go down the tree,
   * until we find a correct place for a new node.
   *
   */

  if (NULL == node) { /* found place for new node */
    ++*num_node;
    return create_node_(key); 
  } 
  
  /* if the same key was found in an existing node,
   * then the tree structure should remain the same
   */
  if (key == node->key_) {
    assert(node->num_key_ > 0);
    ++node->num_key_;
    return node;
  }

  if (key < node->key_) {
    /* Let's try to find a place for a new node in the left subtree */
    node->left_ = insert_key_(node->left_, key, num_node); 

    /* Fix parent of returned node, perfectly works with balance */
    node->left_->parent_ = node;         

  } else if (key > node->key_){   
    /* Let's try to find a place for a new node in the right subtree */
    node->right_ = insert_key_(node->right_, key, num_node);

    /* Fix parent of returned node, perfectly works with balance */
    node->right_->parent_ = node;

  }

  /* 2. Going up.
   *
   * From this moment we have found a place for the new node,
   * and now we begin to climb up the recursion and gradually
   * correct the balance in the nodes until we reach the root.
   *
   */

  /* Recalculate new height of given node */
  node->height_ = get_recalc_height_(node);

  /* Update the balance variable of current node */
  node_balance = get_balance_(node);

#define MAX_BALANCE_TRESHOLD 1
#define MIN_BALANCE_TRESHOLD -1

  /* LL-case: 
   *
   * Disbalance occured in the current node, 
   * after inserting new node into the left subtree 
   * of the left child of our node.
   *
   */
  if (node_balance > MAX_BALANCE_TRESHOLD 
      && node->left_ != NULL
      && key < node->left_->key_)
    return right_rotate_(node); /* parent will be fixed after nearest return */

  /* RR-case:
   *
   * Disbalance occured in the current node,
   * after inserting new node into the right subtree 
   * of the right child of our node.
   *
   */
  if (node_balance < MIN_BALANCE_TRESHOLD 
      && node->right_ != NULL
      && key > node->right_->key_)
    return left_rotate_(node); /* parent will be fixed after nearest return */

  /* LR-case:
   *
   * Disbalance occured in the current node,
   * after inserting new node into the right subtree
   * of the left child of our node.
   *
   */
  if (node_balance > MAX_BALANCE_TRESHOLD 
      && node->left_ != NULL
      && key > node->left_->key_) {
    node->left_ = left_rotate_(node->left_);
    node->left_->parent_ = node;
    node = right_rotate_(node); /* after return parent will be fixed,
                                   or will be null if caller is root */
  }

  /* RL-case:
   *
   * Disbalance occured in the current node,
   * after inserting new node into the left subtree
   * of the right child of our node.
   *
   */
  if (node_balance < MIN_BALANCE_TRESHOLD 
      && node->right_ != NULL
      && key < node->right_->key_) {
    node->right_ = right_rotate_(node->right_);
    node->right_->parent_ = node;
    node = left_rotate_(node); /* after return parent will be fixed,
                                 or will be null if caller is root */
  }

  return node; /* can be changed after balance */
}

/* USER METHODS ========================================================== */

void init_avl(AVL* tree) {
  tree->root_ = NULL;
  tree->num_node_ = 0;
}

Node* insert_key(AVL* tree, int key) {
  if (NULL == tree) return NULL;
  return (tree->root_ = insert_key_(tree->root_, key, &tree->num_node_));
}

void delete_avl(AVL* tree) {
  traverse_postorder(tree, free_node_);
  tree->root_     = NULL;
  tree->num_node_ = 0;
}

u32 get_avl_size(AVL* tree) {
  if (NULL == tree) return 0;
  return tree->num_node_;
}

u32 get_height(const Node* node) {
  return (NULL != node) ? node->height_ : 0;
}

void traverse_postorder(AVL* tree, void (*predicate)(Node*)) {
  if (NULL == tree) return;
  traverse_postorder_(tree->root_, predicate);
}

void traverse_inorder(AVL* tree, void (*predicate)(Node*)) {
  if (NULL == tree) return;
  traverse_inorder_(tree->root_, predicate);
}

void print_avl_nodes(AVL* tree) {
  print_root(tree);
  traverse_inorder(tree, print_node);
}

void print_avl(AVL* tree) {
  traverse_inorder(tree, print_key);
  putchar('\n');
}

void print_root(AVL* tree) {
  if (NULL == tree) return;
  printf("root      : %p \n", tree->root_    );
  printf("num nodes : %u \n", tree->num_node_);
  putchar('\n');
}

void print_node(Node* node) {
  if (NULL == node) return;
  printf("=============================\n");
  printf("|Node      : %-14p |\n", (void*)node);
  printf("|---------------------------|\n");
  printf("|--left    : %-14p |\n", (void*)node->left_);
  printf("|--right   : %-14p |\n", (void*)node->right_);
  printf("|--parent  : %-14p |\n", (void*)node->parent_);
  printf("|---------------------------|\n");
  printf("|--key     : %-14d |\n", node->key_);
  printf("|--num_key : %-14u |\n", node->num_key_);
  printf("|--height  : %-14u |\n", node->height_);
  printf("=============================\n");
  putchar('\n');
}

void print_key(Node* node) {
  if (node == NULL) return;
  printf("%d ", node->key_);
}
