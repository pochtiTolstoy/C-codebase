#include <stdio.h>
#include "../include/tim_list.h"

int main(void) {
	List list;
	init_list(&list);
	for (int i = 0; i < 10; ++i) {
		push(&list, i + 2);
	}
	print_list(&list);
	free_list(&list);
	return 0;
}
