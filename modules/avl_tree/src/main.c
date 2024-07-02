#include <stdio.h>
#include "../include/tim_avl.h"
#include "../include/util.h"

void print_log(AVL* tree) {
  printf("AVL-Tree=======================\n");
  print_avl(tree);
}

void printn_log(AVL* tree) {
  printf("[AVL-Tree-Nodes]===================================\n");
  print_avl_nodes(tree);
  puts("\n\n");
}

int main(void) {
  srand(time(NULL));

  AVL tree;
  init_avl(&tree);

  u32 size = 1000000;
  int in[size];
  fill_array_rand(in, size);

  create_avl_from_array(&tree, in, size);
  /*
  cr_assert(tree.root_, "Tree is not a NULL.");
  cr_assert(!is_avl_empty(&tree), "AVL should not be empty.");
  cr_assert(get_avl_num_elems(&tree) == size, "Wrong elems number.");
  cr_assert(cmp_avl_with_arr(&tree, sort(in, size), size), 
      "Tree is not equal to original array.");
  */
  if (!tree.root_)
    return -1;
  if (is_avl_empty(&tree))
    return -1;
  if (get_avl_num_elems(&tree) != size)
    return -1;
  sort(in, size);
  if (!cmp_avl_with_arr(&tree, in, size))
    return -1;

  delete_avl(&tree);
  /*
  cr_assert(!tree.root_ && tree.num_node_ == 0, 
      "Wrong tree state after deletion.");
  */
  if (tree.root_ || tree.num_node_ != 0)
    return -1;
  return 0;
}
