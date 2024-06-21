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
  insert_key(&tree, 19);
  insert_key(&tree, 13);
  insert_key(&tree, 17);
#endif
  print_bst_nodes(&tree);
  print_bst(&tree);
  delete_bst(&tree);
  assert(tree.root_ == NULL);
	return 0;
}
