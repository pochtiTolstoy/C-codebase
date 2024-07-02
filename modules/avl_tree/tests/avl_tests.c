#include <criterion/criterion.h>
#include "../include/tim_avl.h"
#include "../include/util.h"

Test(avl_tests, insertion1) {
  /* LL, LR */
  AVL tree;
  init_avl(&tree);
  int in[] = { 30, 15, 10, 5, 5, 5, 5, 3, 11, 1, 1 };
  u32 size = (u32) sizeof(in) / sizeof(in[0]);

  create_avl_from_array(&tree, in, size);
  cr_assert(tree.root_, "Tree is not a NULL.");
  cr_assert(get_height(tree.root_) == 3, "Wrong node height.");
  cr_assert(!is_avl_empty(&tree), "AVL is empty.");
  cr_assert(get_avl_size(&tree) == 7, "Wrong nodes number.");
  cr_assert(get_avl_num_elems(&tree) == size, "Wrong elems number.");
  sort(in, size);
  cr_assert(cmp_avl_with_arr(&tree, in, size), 
      "Tree is not equal to original array.");

  delete_avl(&tree);
  cr_assert(!tree.root_ && tree.num_node_ == 0, 
      "Wrong tree state after deletion.");
}

Test(avl_tests, insertion2) {
  srand(time(NULL));
  AVL tree;
  init_avl(&tree);
  u32 size = 1000000;
  int in[size];
  fill_array_rand(in, size);

  create_avl_from_array(&tree, in, size);
  cr_assert(tree.root_, "Tree is not a NULL.");
  cr_assert(!is_avl_empty(&tree), "AVL should not be empty.");
  cr_assert(get_avl_num_elems(&tree) == size, "Wrong elems number.");
  sort(in, size);
  //print_array(in, size);
  cr_assert(cmp_avl_with_arr(&tree, in, size), 
      "Tree is not equal to original array.");

  delete_avl(&tree);
  cr_assert(!tree.root_ && tree.num_node_ == 0, 
      "Wrong tree state after deletion.");
}

Test(avl_tests, insertion3) {
  srand(time(NULL));
  AVL tree;
  init_avl(&tree);
  u32 size = 1000000; 
  int in[size];
  fill_array_incorder(in, size);

  create_avl_from_array(&tree, in, size);
  cr_assert(tree.root_, "Tree is not a NULL.");
  cr_assert(!is_avl_empty(&tree), "AVL should not be empty.");
  cr_assert(get_avl_num_elems(&tree) == size, "Wrong elems number.");
  //print_array(in, size);
  cr_assert(cmp_avl_with_arr(&tree, in, size), 
      "Tree is not equal to original array.");


  delete_avl(&tree);
  cr_assert(!tree.root_ && tree.num_node_ == 0, 
      "Wrong tree state after deletion.");
}

