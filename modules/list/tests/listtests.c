#include <criterion/criterion.h>
#include <string.h>
#include "../include/tim_list.h"

static int square_(int x) { return x * x; }

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

Test(list_tests, exchangenext) {
	List test_list;
	Node* u = NULL;
	Node* v = NULL;
	Node* res = exchangenext(&list, u, v);
	cr_expect(
		res == NULL,
		"NULL pointers are given, expected NULL."
	);

	init_list(&test_list);
	push(&test_list, 123);
	u = find_key(&test_list, 123);
	res = exchangenext(&list, u, v);
	cr_expect(
		res == NULL,	
		"Second pointer is NULL, expected NULL."
	);
	res = exchangenext(&list, v, u);
	cr_expect(
		res == NULL,	
		"First pointer is NULL, expected NULL."
	);

	push(&test_list, 456);
	v = find_key(&test_list, 456);
	res = exchangenext(&list, u, v);
	free_list(&test_list);
	cr_expect(
		res == NULL,
		"Given nodes are not in list."
	);

	push(&list, 10);
	u = find_key(&list, 10);
	res = exchangenext(&list, list.head_, u);

	cr_expect(
		res == NULL,
		"Given node points to last element."
	);
	cr_expect(
		list.rear_ == u,
		"Rear pointer should be vaild."
	);

	res = exchangenext(&list, list.head_, list.tail_);
	cr_expect(
		res == NULL,
		"Given node should not point to tail."
	);

	res = exchangenext(&list, u, list.tail_);
	cr_expect(
		res == NULL,
		"Given node should not point to tail."
	);

	// Trivial cases with neighbour nodes
	List l1;
	init_list(&l1);
	push(&l1, 222);
	push(&l1, 111);
	clear_list(&list);
	push(&list, 111);
	push(&list, 222);
	cr_expect(
		!compare_lists(&list, &l1),
		"Lists should not be equal before exchange."
	);
	res = exchangenext(&list, list.head_, list.head_->next_);
	cr_expect(
		compare_lists(&list, &l1),
		"Lists should be equal after exchange."
	);	
	free_list(&l1);

	List l2;
	init_list(&l2);
	clear_list(&list);
	for (int i = 1; i <= 10000; ++i) {
		push(&l2, square_(i));
	}
	u = push(&list, square_(2));
	v = push(&list, square_(1));
	for (int i = 3; i <= 10000; ++i) {
		push(&list, square_(i));
	}
	
	cr_expect(
		!compare_lists(&list, &l2),
		"Lists should not be equal before exchange."
	);
	exchangenext(&list, get_prev_node(&list, u), get_prev_node(&list, v));
	cr_expect(
		compare_lists(&list, &l2),
		"Lists should be equal after exchange."
	);	

	free_list(&l2);
}
