#include <stdio.h>
#include "../include/tim_bin_tree.h"

int main(void) {
  printf("Hello, binary search tree!\n");
  BST tree;
  init_bst(&tree);
#if 0
  insert_key(&tree, 12);
  insert_key(&tree, 5);
  insert_key(&tree, 2);
  insert_key(&tree, 9);
  insert_key(&tree, 18);
  insert_key(&tree, 15);
  Node* tmp1 = insert_key(&tree, 19);
  Node* tmp2 = insert_key(&tree, 10);
  insert_key(&tree, 2);
  Node* tmp3 = insert_key(&tree, 13);
  insert_key(&tree, 17);
  print_bst(&tree);
  Node* catch = find_key(&tree, 18);
  print_node(catch);
  delete_node(&tree, catch);
  print_bst(&tree);
  printf("\nMin Max:\n");
  print_node(get_min(tree.root_));
  print_node(get_max(tree.root_));
  printf("Lower bound of 19:\n");
  print_node(lower_bound(tmp1));
  print_node(upper_bound(tmp2));
  print_node(lower_bound(tmp3));
#endif
  insert_key(&tree, 2);
  insert_key(&tree, 0);
  insert_key(&tree, 10);
  insert_key(&tree, 8);
  insert_key(&tree, 5);
  insert_key(&tree, -2);
  insert_key(&tree, -1);
  insert_key(&tree, 3);
  insert_key(&tree, 4);
  insert_key(&tree, 11);
  insert_key(&tree, 7);
  insert_key(&tree, 9);

  print_bst(&tree);
  printf("size of tree: %d\n", size(&tree));

  delete_bst(&tree);
  assert(tree.root_ == NULL);
	return 0;
}
