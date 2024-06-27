#include <stdio.h>
#include "../include/tim_avl.h"

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
  printf("Hello world!\n");

  AVL t1;
  init_avl(&t1);

  printn_log(&t1);

  insert_key(&t1, 30);
  printn_log(&t1);

  insert_key(&t1, 15);
  printn_log(&t1);

  insert_key(&t1, 10);
  printn_log(&t1);

  insert_key(&t1, 5);
  printn_log(&t1);

  insert_key(&t1, 3);
  printn_log(&t1);

  insert_key(&t1, 1);
  printn_log(&t1);


  delete_avl(&t1);
  printn_log(&t1);
  return 0;
}
