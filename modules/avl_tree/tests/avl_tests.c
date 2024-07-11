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

Test(avl_tests, deletion1) {
  AVL tree;
  init_avl(&tree);
  insert_key(&tree, 10);

  cr_assert(tree.root_->key_ == 10, "Wrong key value in tree.");

  delete_key(&tree, 10);

  cr_assert(tree.root_ == NULL, "Root should be empty after deleting node.");
  cr_assert(tree.num_node_ == 0, "Wrong node counter value.");

  u32 size = 10;
  for (u32 i = 0; i < size; ++i) {
    insert_key(&tree, i);
  }

  cr_assert(cmp_avl_with_string(&tree, "0 1 2 3 4 5 6 7 8 9") == true,
      "Invalid key sequence.");

  delete_key(&tree, 1);

  cr_assert(cmp_avl_with_string(&tree, "0 2 3 4 5 6 7 8 9") == true,
      "Invalid key sequence.");

  delete_key(&tree, 9);

  cr_assert(cmp_avl_with_string(&tree, "0 2 3 4 5 6 7 8") == true,
      "Invalid key sequence.");
  delete_key(&tree, 0);

  cr_assert(cmp_avl_with_string(&tree, "2 3 4 5 6 7 8") == true,
      "Invalid key sequence.");

  delete_key(&tree, 5);

  cr_assert(cmp_avl_with_string(&tree, "2 3 4 6 7 8") == true,
      "Invalid key sequence.");

  delete_key(&tree, 7);

  cr_assert(cmp_avl_with_string(&tree, "2 3 4 6 8") == true,
      "Invalid key sequence.");

  insert_key(&tree, 100);
  cr_assert(cmp_avl_with_string(&tree, "2 3 4 6 8 100") == true,
      "Invalid key sequence.");

  delete_key(&tree, 100);

  delete_key(&tree, 2);

  cr_assert(cmp_avl_with_string(&tree, "3 4 6 8") == true,
      "Invalid key sequence.");

  delete_key(&tree, 4);

  cr_assert(cmp_avl_with_string(&tree, "3 6 8") == true,
      "Invalid key sequence.");

  delete_key(&tree, 6);

  cr_assert(cmp_avl_with_string(&tree, "3 8") == true,
      "Invalid key sequence.");

  delete_key(&tree, 8);

  cr_assert(cmp_avl_with_string(&tree, "3") == true,
      "Invalid key sequence.");

  delete_avl(&tree);
  cr_assert(!tree.root_ && tree.num_node_ == 0, 
      "Wrong tree state after deletion.");
}


Test(avl_tests, deletion_LL1) {
  AVL tree;
  init_avl(&tree);
  insert_key(&tree, 20);
  insert_key(&tree, 25);
  insert_key(&tree, 10);
  insert_key(&tree, 23);
  insert_key(&tree, 5);
  insert_key(&tree, 15);
  insert_key(&tree, 1);

  cr_assert(cmp_avl_with_string(&tree, "1 5 10 15 20 23 25") == true,
      "Invalid key sequence.");

  delete_key(&tree, 23);
  cr_assert(cmp_avl_with_string(&tree, "1 5 10 15 20 25") == true,
      "Invalid key sequence.");

  cr_assert(tree.root_->key_ == 10, "Wrong root node.");

  delete_avl(&tree);
  cr_assert(!tree.root_ && tree.num_node_ == 0, 
      "Wrong tree state after deletion.");
}

Test(avl_tests, key_repeat1) {
  AVL tree;
  init_avl(&tree);

  for (u32 i = 0; i < 5; ++i) {
    insert_key(&tree, 10);
  }

  cr_assert(cmp_avl_with_string(&tree, "10 10 10 10 10"), 
      "Invalid key sequence");

  cr_assert(get_avl_size(&tree) == 1, "Wrong node counter.");
  cr_assert(get_avl_num_elems(&tree) == 5, "Wrong key counter.");

  for (u32 i = 0; i < 4; ++i) {
    insert_key(&tree, 20);
  }

  cr_assert(cmp_avl_with_string(&tree, "10 10 10 10 10 20 20 20 20"), 
      "Invalid key sequence");

  cr_assert(get_avl_size(&tree) == 2, "Wrong node counter.");
  cr_assert(get_avl_num_elems(&tree) == 9, "Wrong key counter.");

  delete_key(&tree, 10);

  cr_assert(cmp_avl_with_string(&tree, "10 10 10 10 20 20 20 20"), 
      "Invalid key sequence");
  cr_assert(get_avl_size(&tree) == 2, "Wrong node counter.");
  cr_assert(get_avl_num_elems(&tree) == 8, "Wrong key counter.");

  /* should be ok too */
  for (u32 i = 0; i < 20; ++i)
    delete_key(&tree, 10);

  cr_assert(cmp_avl_with_string(&tree, "20 20 20 20"), 
      "Invalid key sequence");
  cr_assert(get_avl_size(&tree) == 1, "Wrong node counter.");
  cr_assert(get_avl_num_elems(&tree) == 4, "Wrong key counter.");

  for (u32 i = 0; i < 3; ++i)
    delete_key(&tree, 20);


  cr_assert(cmp_avl_with_string(&tree, "20"), 
      "Invalid key sequence");
  cr_assert(get_avl_size(&tree) == 1, "Wrong node counter.");
  cr_assert(get_avl_num_elems(&tree) == 1, "Wrong key counter.");

  delete_avl(&tree);
  cr_assert(!tree.root_ && tree.num_node_ == 0, 
      "Wrong tree state after deletion.");
  cr_assert(get_avl_size(&tree) == 0, "Wrong node counter.");
  cr_assert(get_avl_num_elems(&tree) == 0, "Wrong elems counter.");
}
