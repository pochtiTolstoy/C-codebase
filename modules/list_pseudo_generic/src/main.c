#include <stdio.h>
#include "../include/tim_listg.h"

int main(void) {
	printf("Hello world!\n");

	List list;
	init_list(&list, "d");
  push(&list, 100);
  for (int i = 200; i <= 1000; i += 50) {
    push(&list, i);
  }
	print_list(&list);

  free_list(&list);
	return 0;
}
