#include <stdio.h>
#include "m_list.h"

int main(void) {
	List list;	
	init_list(&list);
	enqueue(&list, 10);
	print_list(&list);
	enqueue(&list, 2);
	print_list(&list);
	dequeue(&list);
	print_list(&list);
	dequeue(&list);
	print_list(&list);
	for (int i = 0; i < 3; ++i) {
		enqueue(&list, 2);
	}
	print_list(&list);
	clear_list(&list);
	print_list(&list);
	enqueue(&list, 190);
	enqueue(&list, 200);
	enqueue(&list, 210);
	enqueue(&list, 220);
	enqueue(&list, 230);
	print_list(&list);
	dequeue(&list);
	print_list(&list);
	dequeue(&list);
	print_list(&list);
	dequeue(&list);
	print_list(&list);
	dequeue(&list);
	print_list(&list);
	dequeue(&list);
	print_list(&list);

	push(&list, 190);
	push(&list, 200);
	push(&list, 210);
	push(&list, 220);
	push(&list, 230);
	print_list(&list);
	pop(&list);
	print_list(&list);
	pop(&list);
	print_list(&list);
	pop(&list);
	print_list(&list);
	pop(&list);
	print_list(&list);
	pop(&list);
	print_list(&list);

	free_list(&list);
	return 0;
}
