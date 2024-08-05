#include <stdio.h>
#include "../include/tim_listg.h"

int main(void) {
	printf("Hello world!\n");

	List list;
  const char* str = "Hello, my name is Timur!";
	init_list(&list, "d");
  push(&list, 100);
  for (int i = 200; i <= 1000; i += 50) {
    push(&list, i);
  }
	print_list(&list);
  int64_t elem = pop(&list).decimal; 
  printf("poped: %ld.\n", elem);
	print_list(&list);

  List list_str;
  init_list(&list_str, "s");
  push(&list_str, str);
  push(&list_str, "This is very informative string.");
  push(&list_str, "I love you.");
  print_list(&list_str);
  printf("Poped str: %s\n", pop(&list_str).string);
  print_list(&list_str);

  free_list(&list);
  free_list(&list_str);
	return 0;
}
