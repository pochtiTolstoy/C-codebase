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

#if 0
  u32 size = 1000;
  int in[size];
  fill_array_rand(in, size);

  create_avl_from_array(&tree, in, size);
#endif

  for (int i = 0; i < 10; ++i) {
    insert_key(&tree, i);
    printn_log(&tree);
  }
  delete_key(&tree, 1);
  printn_log(&tree);
  delete_key(&tree, 9);
  printn_log(&tree);
  delete_key(&tree, 0);
  printn_log(&tree);
  delete_key(&tree, 5);
  printn_log(&tree);
  delete_key(&tree, 7);
  printn_log(&tree);
  delete_key(&tree, 2);
  printn_log(&tree);
  delete_key(&tree, 4);
  printn_log(&tree);
  delete_key(&tree, 6);
  printn_log(&tree);
  delete_key(&tree, 8);
  printn_log(&tree);
#if 0
#endif

#if 0
  if (!tree.root_)
    return -1;
  if (is_avl_empty(&tree))
    return -1;
  if (get_avl_num_elems(&tree) != size)
    return -1;
  sort(in, size);
  if (!cmp_avl_with_arr(&tree, in, size))
    return -1;
#endif

  delete_avl(&tree);
  if (tree.root_ || tree.num_node_ != 0)
    return -1;
  return 0;
}
