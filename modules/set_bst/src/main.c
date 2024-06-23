#include <stdio.h>
#include "../include/tim_set_bst.h"

int main(void) {
	printf("Hello, binary tree set!\n");	
	Set set;
	init_set(&set);
	for (int i = 10; i > 0; --i) {
		set_insert(&set, i);
		print_set(&set);
		printf("size: %d\n\n", set_size(&set));
	}
	for (int i = 5; i > 0; --i) {
		set_insert(&set, i);
		print_set(&set);
		printf("size: %d\n\n", set_size(&set));
	}

	set_insert(&set, 5);
	print_set(&set);
	printf("size: %d\n\n", set_size(&set));
	set_insert(&set, -10);
	print_set(&set);
	printf("size: %d\n\n", set_size(&set));

	clear_set(&set);
	return 0;
}
