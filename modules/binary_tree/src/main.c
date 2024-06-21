#include <stdio.h>
#include "../include/tim_bin_tree.h"

int main(void) {
  printf("Hello, binary search tree!\n");
  BST tree;
  init_bst(&tree);
  insert_key(&tree, 12);
  insert_key(&tree, 5);
  insert_key(&tree, 2);
#if 1
  insert_key(&tree, 9);
  insert_key(&tree, 18);
  insert_key(&tree, 15);
  Node* tmp1 = insert_key(&tree, 19);
  Node* tmp2 = insert_key(&tree, 10);
  insert_key(&tree, 2);
  Node* tmp3 = insert_key(&tree, 13);
  insert_key(&tree, 17);
#endif
  Node* catch = find_key(&tree, 18);
  print_node(catch);
  print_bst_nodes(&tree);
  print_bst(&tree);
  printf("\nMin Max:\n");
  print_node(get_min(tree.root_));
  print_node(get_max(tree.root_));
  printf("Lower bound of 19:\n");
  print_node(lower_bound(tmp1));
  print_node(upper_bound(tmp2));
  print_node(lower_bound(tmp3));
  delete_bst(&tree);
  assert(tree.root_ == NULL);
	return 0;
}
