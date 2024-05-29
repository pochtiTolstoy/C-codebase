#include <stdio.h>
#include "list.h"

void print_item(Item item);

int main(void) {
  char str[SSIZE];
  List l1;
  init_list(&l1);
  insert(&l1, "Hello world!");
  insert(&l1, "Cats are great,");
  insert(&l1, "And dogs too!");
  traverse(&l1, print_item);
  printf("items: %u\n", item_count(&l1));
  if (delete_item(&l1, "Hello world!"))
    printf("Delete\n");
  else
    printf("Not delete\n");
  traverse(&l1, print_item);
  printf("items: %u\n", item_count(&l1));
  insert(&l1, "Pizza and coffee");
  if (pop(&l1, str))
    printf("Popped string: %s\n", str);
  printf("items: %u\n", item_count(&l1));
  empty_the_list(&l1);
  return 0;
}

void print_item(Item item) {
  printf("%s\n", item);
}
