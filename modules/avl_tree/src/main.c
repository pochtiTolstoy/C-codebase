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
  printf("%d\n", cmp_avl_with_string(&tree, "0 1 2 3 4 5 6 7 8 9"));
  delete_key(&tree, 1);
  printf("%d\n", cmp_avl_with_string(&tree, "0 2 3 4 5 6 7 8 9"));
  delete_key(&tree, 9);
  printf("%d\n", cmp_avl_with_string(&tree, "0 2 3 4 5 6 7 8"));
  delete_key(&tree, 0);
  printf("%d\n", cmp_avl_with_string(&tree, "2 3 4 5 6 7 8"));
  delete_key(&tree, 5);
  printf("%d\n", cmp_avl_with_string(&tree, "2 3 4 6 7 8"));
  delete_key(&tree, 7);
  printf("%d\n", cmp_avl_with_string(&tree, "2 3 4 6 8"));
  delete_key(&tree, 2);
  printf("%d\n", cmp_avl_with_string(&tree, "3 4 6 8"));
  delete_key(&tree, 4);
  printf("%d\n", cmp_avl_with_string(&tree, "3 6 8"));
  delete_key(&tree, 6);
  printf("%d\n", cmp_avl_with_string(&tree, "3 8"));
  delete_key(&tree, 8);
  printf("%d\n", cmp_avl_with_string(&tree, "3"));

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
