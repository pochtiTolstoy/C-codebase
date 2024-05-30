#include <criterion/criterion.h>
#include <string.h>
#include "../include/tim_list.h"

List list;
void setup(void) {
	init_list(&list);
}

void teardown(void) {
	free_list(&list);
}

void suite_empty_list(void) {
	cr_assert(list.head_ != NULL && list.tail_ != NULL,
			"init_list should create head and tail nodes."
	);
	cr_assert(
			list.size_ == 0, 
			"List size should be 0"
	);
	cr_assert(
			list.head_->next_ == list.tail_, 
			"Head and Tail should be connected"
	);
	cr_assert(
			list.tail_->next_ == list.tail_, 
			"Tail should be cycled node"
	);
	cr_assert(
			list.rear_ == NULL, 
			"Rear pointer should be null"
	);
}

TestSuite(list_tests, .init = setup, .fini = teardown);

Test(list_tests, initialization) {
	suite_empty_list();
}

Test(list_tests, clear_list) {
	clear_list(&list);
	suite_empty_list();

	push(&list, 1);
	clear_list(&list);
	suite_empty_list();

	for (int i = 0; i < get_list_capacity() * 2; ++i) {
		push(&list, i * 2);
	}
	cr_expect(
			get_list_size(&list) == get_list_capacity(), 
			"Expected size == capacity."
	);
	cr_expect(
			list.rear_->key_ == 0,
			"Rear key should be equal to last element"
	);
	clear_list(&list);
	suite_empty_list();

	for (int i = 0; i < 10; ++i) {
		push(&list, 1);
	}
	for (int i = 0; i < 5; ++i) {
		pop(&list);
	}
	push(&list, 2);
	clear_list(&list);
	suite_empty_list();
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
