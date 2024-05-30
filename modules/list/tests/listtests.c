#include <criterion/criterion.h>
#include <string.h>
#include "../include/tim_list.h"

List list;

void suite_setup(void) {
	init_list(&list);
}

void suite_teardown(void) {
	free_list(&list);	
}

TestSuite(list_tests, .init=suite_setup, .fini=suite_teardown);

Test(list_tests, initialization) {
	cr_expect(list.head_ != NULL && list.tail_ != NULL,
			"init_list should create head and tail nodes.\n"
	);
}

Test(list_tests, pushing_elements) {
	cr_expect(
		list.head_->next_ == list.tail_,
		"Expected head and tail node in list after initialization."
	);

	push(&list, 1);

	cr_expect(
		list.head_->next_ != list.tail_,
		"Head next pointer should point to pushed node, not tail."
	);

	cr_expect(
		list.head_->next_->next_ == list.tail_,
		"First pushed node should point to the tail."
	);

	cr_expect(
		list.head_->next_->key_ = 1,
		"Wrong key in pushed node."
	);

	cr_expect(
		list.rear_ == list.head_->next_,
		"Pointer to last node should point to first pushed node."
	);
}
