#include <stdio.h>
#include "../include/tim_dl_list_s.h"

int main(void) {
	printf("Hello world!\n");
	List l1;
	init_list(&l1);
	push(&l1, ".");
	push(&l1, "bye");
	push(&l1, ", ");
	push(&l1, "Good");
	print_list(&l1);	
	free_list(&l1);
	return 0;
}
