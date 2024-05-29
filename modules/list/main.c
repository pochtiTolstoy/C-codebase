#include <stdio.h>
#include "m_list.h"

#define basic_test 0
#define test_movenexttofront 0

int main(void) {
	List list;	
	List l2;
	init_list(&list);
	init_list(&l2);
#if basic_test
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
#endif /* basic_test */

#if test_movenexttofront
	push(&list, 10);
	push(&list, 20);
	push(&list, 21);
	push(&list, 22);
	push(&list, 23);
	print_list(&list);
	movenexttofront(&list, find_key(&list, 10));
	print_list(&list);
	printf("Rear->key: %d\n", list.rear_->key_);
	movenexttofront(&list, find_key(&list, 20));
	print_list(&list);
	printf("Rear->key: %d\n", list.rear_->key_);

	movenexttofront(&list, find_key(&list, 21));
	print_list(&list);
	printf("Rear->key: %d\n", list.rear_->key_);

	movenexttofront(&list, find_key(&list, 22));
	print_list(&list);
	printf("Rear->key: %d\n", list.rear_->key_);

	movenexttofront(&list, find_key(&list, 23));
	print_list(&list);
	printf("Rear->key: %d\n", list.rear_->key_);

	movenexttofront(&list, find_key(&list, 10));
	print_list(&list);
	printf("Rear->key: %d\n", list.rear_->key_);


	push(&l2, -20);
	push(&l2, -10);
	print_list(&l2);
	printf("Rear->key: %d\n", l2.rear_->key_);
	movenexttofront(&l2, find_key(&list, 23));
	movenexttofront(&l2, find_key(&l2, -10));
	print_list(&l2);
	printf("Rear->key: %d\n", l2.rear_->key_);

	clear_list(&list);
	printf("Rear: %p\n", list.rear_);


#endif /* test_movenexttofront */

	free_list(&list);
	free_list(&l2);
	return 0;
}
