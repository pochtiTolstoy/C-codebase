#include <criterion/criterion.h>
#include "../include/tim_avl.h"
#include "../include/util.h"

extern bool is_array_sorted(int [], u32); /* util.h */

#if AUTO_BALANCE_
#else
/* without autobalance tree should be a bamboo after inserting sorted order */
Test(avl_tests, bamboo1) {
  AVL tree;
  init_avl(&tree);
  for (int i = 0; i < 10; ++i) {
    insert_key(&tree, i);
  }
  cr_assert(tree.root_->key_ == 0, "Wrong tree root.");
  cr_assert(tree.root_->left_ == NULL, "Tree should be bamboo.");
  cr_assert(
    true == cmp_avl_with_string(
      &tree, 
      "0 1 2 3 4 5 6 7 8 9"
    ),
    "Invalid key sequence."
  );

  delete_avl(&tree);
}
#endif

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
  cr_assert(is_balanced(&tree) == true, "Tree is not balanced.");

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

  cr_assert(is_balanced(&tree) == true, "Tree is not balanced.");

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
  cr_assert(cmp_avl_with_arr(&tree, in, size), 
      "Tree is not equal to original array.");

  cr_assert(is_balanced(&tree) == true, "Tree is not balanced.");


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
  cr_assert(is_balanced(&tree) == true, "Tree is not balanced.");

  delete_key(&tree, 1);

  cr_assert(cmp_avl_with_string(&tree, "0 2 3 4 5 6 7 8 9") == true,
      "Invalid key sequence.");
  cr_assert(is_balanced(&tree) == true, "Tree is not balanced.");

  delete_key(&tree, 9);

  cr_assert(cmp_avl_with_string(&tree, "0 2 3 4 5 6 7 8") == true,
      "Invalid key sequence.");
  cr_assert(is_balanced(&tree) == true, "Tree is not balanced.");

  delete_key(&tree, 0);

  cr_assert(cmp_avl_with_string(&tree, "2 3 4 5 6 7 8") == true,
      "Invalid key sequence.");
  cr_assert(is_balanced(&tree) == true, "Tree is not balanced.");

  delete_key(&tree, 5);

  cr_assert(cmp_avl_with_string(&tree, "2 3 4 6 7 8") == true,
      "Invalid key sequence.");
  cr_assert(is_balanced(&tree) == true, "Tree is not balanced.");

  delete_key(&tree, 7);

  cr_assert(cmp_avl_with_string(&tree, "2 3 4 6 8") == true,
      "Invalid key sequence.");
  cr_assert(is_balanced(&tree) == true, "Tree is not balanced.");

  insert_key(&tree, 100);
  cr_assert(cmp_avl_with_string(&tree, "2 3 4 6 8 100") == true,
      "Invalid key sequence.");
  cr_assert(is_balanced(&tree) == true, "Tree is not balanced.");

  delete_key(&tree, 100);

  delete_key(&tree, 2);

  cr_assert(is_balanced(&tree) == true, "Tree is not balanced.");

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
  cr_assert(is_balanced(&tree) == true, "Tree is not balanced.");

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
  cr_assert(is_balanced(&tree) == true, "Tree is not balanced.");

  cr_assert(cmp_avl_with_string(&tree, "1 5 10 15 20 23 25") == true,
      "Invalid key sequence.");

  delete_key(&tree, 23);
  cr_assert(cmp_avl_with_string(&tree, "1 5 10 15 20 25") == true,
      "Invalid key sequence.");

  cr_assert(tree.root_->key_ == 10, "Wrong root node.");
  cr_assert(is_balanced(&tree) == true, "Tree is not balanced.");

  delete_avl(&tree);
  cr_assert(!tree.root_ && tree.num_node_ == 0, 
      "Wrong tree state after deletion.");
}

Test(avl_tests, deleteion_RR1) {
  AVL tree;
  init_avl(&tree);
  insert_key(&tree, 20);
  insert_key(&tree, 10);
  insert_key(&tree, 30);
  insert_key(&tree, 5);
  insert_key(&tree, 25);
  insert_key(&tree, 35);
  insert_key(&tree, 40);

  cr_assert(is_balanced(&tree) == true, "Tree is not balanced.");
  
  cr_assert(cmp_avl_with_string(&tree, "5 10 20 25 30 35 40") == true,
      "Invalid key sequence.");

  delete_key(&tree, 5); 
  cr_assert(tree.root_->key_ == 30, "Wrong tree root");
  cr_assert(cmp_avl_with_string(&tree, "10 20 25 30 35 40") == true,
      "Invalid key sequence.");
  cr_assert(is_balanced(&tree) == true, "Tree is not balanced.");

  delete_avl(&tree);
  cr_assert(!tree.root_ && tree.num_node_ == 0, 
      "Wrong tree state after deletion.");
  cr_assert(get_avl_size(&tree) == 0, "Wrong node counter.");
  cr_assert(get_avl_num_elems(&tree) == 0, "Wrong elems counter.");
}

Test(avl_test, deletion_RL1) {
  AVL tree;
  init_avl(&tree);
  insert_key(&tree, 20);
  insert_key(&tree, 10);
  insert_key(&tree, 30);
  insert_key(&tree, 5);
  insert_key(&tree, 25);
  insert_key(&tree, 35);
  insert_key(&tree, 23);
  cr_assert(is_balanced(&tree) == true, "Tree is not balanced.");
  
  cr_assert(cmp_avl_with_string(&tree, "5 10 20 23 25 30 35") == true,
      "Invalid key sequence.");

  delete_key(&tree, 5); 
  cr_assert(tree.root_->key_ == 25, "Wrong tree root");
  cr_assert(cmp_avl_with_string(&tree, "10 20 23 25 30 35") == true,
      "Invalid key sequence.");
  cr_assert(is_balanced(&tree) == true, "Tree is not balanced.");

  delete_avl(&tree);
  cr_assert(!tree.root_ && tree.num_node_ == 0, 
      "Wrong tree state after deletion.");
  cr_assert(get_avl_size(&tree) == 0, "Wrong node counter.");
  cr_assert(get_avl_num_elems(&tree) == 0, "Wrong elems counter.");
}

Test(avl_test, deletion_LR1) {
  AVL tree;
  init_avl(&tree);
  insert_key(&tree, 25);
  insert_key(&tree, 15);
  insert_key(&tree, 30);
  insert_key(&tree, 5);
  insert_key(&tree, 20);
  insert_key(&tree, 35);
  insert_key(&tree, 23);
  cr_assert(is_balanced(&tree) == true, "Tree is not balanced.");
  
  cr_assert(cmp_avl_with_string(&tree, "5 15 20 23 25 30 35") == true,
      "Invalid key sequence.");

  delete_key(&tree, 35); 
  cr_assert(tree.root_->key_ == 20, "Wrong tree root");
  cr_assert(cmp_avl_with_string(&tree, "5 15 20 23 25 30") == true,
      "Invalid key sequence.");
  cr_assert(is_balanced(&tree) == true, "Tree is not balanced.");

  delete_avl(&tree);
  cr_assert(!tree.root_ && tree.num_node_ == 0, 
      "Wrong tree state after deletion.");
  cr_assert(get_avl_size(&tree) == 0, "Wrong node counter.");
  cr_assert(get_avl_num_elems(&tree) == 0, "Wrong elems counter.");
}

Test(avl_test, deletion_RL2) {
  AVL tree;
  AVL test_tree;
  init_avl(&tree);
  init_avl(&test_tree);

  insert_key(&tree, 20);
  insert_key(&tree, 10);
  insert_key(&tree, 35);
  insert_key(&tree, 5);
  insert_key(&tree, 15);
  insert_key(&tree, 25);
  insert_key(&tree, 40);
  insert_key(&tree, 1);
  insert_key(&tree, 24);
  insert_key(&tree, 30);
  insert_key(&tree, 45);
  insert_key(&tree, 33);
  cr_assert(is_balanced(&tree) == true, "Tree is not balanced.");
  
  cr_assert(
      true == cmp_avl_with_string(
        &tree, 
        "1 5 10 15 20 24 25 30 33 35 40 45"
      ),
      "Invalid key sequence."
  );

  delete_key(&tree, 1); 
  cr_assert(is_balanced(&tree) == true, "Tree is not balanced.");
  cr_assert(tree.root_->key_ == 25, "Wrong tree root");
  cr_assert(
      true == cmp_avl_with_string(
        &tree, 
        "5 10 15 20 24 25 30 33 35 40 45"
      ),
      "Invalid key sequence."
  );

  /* creating correct tree structure */
  insert_key(&test_tree, 25);

  insert_key(&test_tree, 20);
  insert_key(&test_tree, 35);

  insert_key(&test_tree, 10);
  insert_key(&test_tree, 24);
  insert_key(&test_tree, 30);
  insert_key(&test_tree, 40);
  
  insert_key(&test_tree, 5);
  insert_key(&test_tree, 15);
  insert_key(&test_tree, 33);
  insert_key(&test_tree, 45);

  cr_assert(
      cmp_avl(&tree, &test_tree) == true, 
      "Tree structures are different."
  );

  cr_assert(is_balanced(&tree) == true, "Tree is not balanced");

  delete_avl(&tree);
  delete_avl(&test_tree);
  cr_assert(!tree.root_ && tree.num_node_ == 0, 
      "Wrong tree state after deletion.");
  cr_assert(get_avl_size(&tree) == 0, "Wrong node counter.");
  cr_assert(get_avl_num_elems(&tree) == 0, "Wrong elems counter.");
}


Test(avl_tests, key_repeat1) {
  AVL tree;
  init_avl(&tree);

  for (u32 i = 0; i < 5; ++i) {
    insert_key(&tree, 10);
  }
  cr_assert(is_balanced(&tree) == true, "Tree is not balanced.");

  cr_assert(cmp_avl_with_string(&tree, "10 10 10 10 10"), 
      "Invalid key sequence");

  cr_assert(get_avl_size(&tree) == 1, "Wrong node counter.");
  cr_assert(get_avl_num_elems(&tree) == 5, "Wrong key counter.");

  for (u32 i = 0; i < 4; ++i) {
    insert_key(&tree, 20);
  }
  cr_assert(is_balanced(&tree) == true, "Tree is not balanced.");

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
  cr_assert(is_balanced(&tree) == true, "Tree is not balanced.");


  cr_assert(cmp_avl_with_string(&tree, "20"), 
      "Invalid key sequence");
  cr_assert(get_avl_size(&tree) == 1, "Wrong node counter.");
  cr_assert(get_avl_num_elems(&tree) == 1, "Wrong key counter.");
  cr_assert(is_balanced(&tree) == true, "Tree is not balanced.");

  delete_avl(&tree);
  cr_assert(!tree.root_ && tree.num_node_ == 0, 
      "Wrong tree state after deletion.");
  cr_assert(get_avl_size(&tree) == 0, "Wrong node counter.");
  cr_assert(get_avl_num_elems(&tree) == 0, "Wrong elems counter.");
}

Test(avl_test, key_repeat2) {
  AVL tree;
  init_avl(&tree);

  for (u32 i = 0; i < 5; ++i) {
    insert_key(&tree, i);
  }
  cr_assert(is_balanced(&tree) == true, "Tree is not balanced.");

  cr_assert(cmp_avl_with_string(&tree, "0 1 2 3 4"), 
      "Invalid key sequence");

  for (u32 i = 0; i < 5; ++i) {
    insert_key(&tree, i);
  }

  cr_assert(cmp_avl_with_string(&tree, "0 0 1 1 2 2 3 3 4 4"), 
      "Invalid key sequence");
  
  delete_key(&tree, 2);
  delete_key(&tree, 4);
  delete_key(&tree, 0);
  cr_assert(is_balanced(&tree) == true, "Tree is not balanced.");

  cr_assert(cmp_avl_with_string(&tree, "0 1 1 2 3 3 4"), 
      "Invalid key sequence");

  delete_key(&tree, 0);
  delete_key(&tree, 3);
  delete_key(&tree, 3);
  cr_assert(is_balanced(&tree) == true, "Tree is not balanced.");

  cr_assert(cmp_avl_with_string(&tree, "1 1 2 4"), 
      "Invalid key sequence");

  delete_avl(&tree);
  cr_assert(!tree.root_ && tree.num_node_ == 0, 
      "Wrong tree state after deletion.");
  cr_assert(get_avl_size(&tree) == 0, "Wrong node counter.");
  cr_assert(get_avl_num_elems(&tree) == 0, "Wrong elems counter.");
}

Test(avl_test, lower_bound1) {
  AVL tree;
  init_avl(&tree);

  int arr[] = { 30, 10, 50, 5, 20, 40, 15, 25 };
  const u32 size = sizeof(arr) / sizeof(arr[0]);
  create_avl_from_array(&tree, arr, size);
  cr_assert(lower_bound(find_key(&tree, 30))->key_ == 25, 
      "Wrong lower bound value");
  cr_assert(lower_bound(find_key(&tree, 15))->key_ == 10, 
      "Wrong lower bound value");
  cr_assert(lower_bound(find_key(&tree, 5)) == NULL, 
      "Wrong lower bound value");
  cr_assert(lower_bound(find_key(&tree, 10))->key_ == 5, 
      "Wrong lower bound value");
  cr_assert(lower_bound(find_key(&tree, 25))->key_ == 20, 
      "Wrong lower bound value");
  cr_assert(lower_bound(find_key(&tree, 20))->key_ == 15, 
      "Wrong lower bound value");
  cr_assert(lower_bound(find_key(&tree, 40))->key_ == 30, 
      "Wrong lower bound value");
  cr_assert(lower_bound(find_key(&tree, 50))->key_ == 40, 
      "Wrong lower bound value");

  delete_avl(&tree);
  cr_assert(!tree.root_ && tree.num_node_ == 0, 
      "Wrong tree state after deletion.");
  cr_assert(get_avl_size(&tree) == 0, "Wrong node counter.");
  cr_assert(get_avl_num_elems(&tree) == 0, "Wrong elems counter.");
}


Test(avl_test, upper_bound1) {
  AVL tree;
  init_avl(&tree);

  int arr[] = { 30, 10, 50, 5, 20, 40, 15, 25 };
  const u32 size = sizeof(arr) / sizeof(arr[0]);
  create_avl_from_array(&tree, arr, size);
  cr_assert(upper_bound(find_key(&tree, 5))->key_ == 10, 
      "Wrong upper bound value");
  cr_assert(upper_bound(find_key(&tree, 10))->key_ == 15, 
      "Wrong upper bound value");
  cr_assert(upper_bound(find_key(&tree, 15))->key_ == 20, 
      "Wrong upper bound value");
  cr_assert(upper_bound(find_key(&tree, 25))->key_ == 30, 
      "Wrong upper bound value");
  cr_assert(upper_bound(find_key(&tree, 20))->key_ == 25, 
      "Wrong upper bound value");
  cr_assert(upper_bound(find_key(&tree, 40))->key_ == 50, 
      "Wrong upper bound value");
  cr_assert(upper_bound(find_key(&tree, 30))->key_ == 40, 
      "Wrong upper bound value");
  cr_assert(upper_bound(find_key(&tree, 50)) == NULL, 
      "Wrong upper bound value");

  delete_avl(&tree);
  cr_assert(!tree.root_ && tree.num_node_ == 0, 
      "Wrong tree state after deletion.");
  cr_assert(get_avl_size(&tree) == 0, "Wrong node counter.");
  cr_assert(get_avl_num_elems(&tree) == 0, "Wrong elems counter.");
}

Test(avl_test, sorting1) {
  const u32 size = 1000;
  int arr[size];
  fill_array_rand(arr, size);
  avl_sort(arr, size);

  cr_assert(is_array_sorted(arr, size), "Array is not sorted");

  avl_sort(arr, size);
  cr_assert(is_array_sorted(arr, size), "Incorder array is not sorted");

  const u32 size2 = 1000000;
  int arr2[size2];
  fill_array_rand(arr2, size2);
  avl_sort(arr2, size2);
  
  cr_assert(is_array_sorted(arr2, size2), "Large array is not sorted");
}
