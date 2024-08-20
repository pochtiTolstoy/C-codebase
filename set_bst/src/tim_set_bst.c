#include "../include/tim_set_bst.h"

void init_set(Set* set) {
	init_bst(&set->tree_);
}

void set_insert(Set* set, int key) {
	insert_key(&set->tree_, key);
}

void set_remove_(Set* set, int key) {
	Node* del_node;
	if (!(del_node = find_key(&set->tree_, key))) return;
	delete_node(&set->tree_, del_node);
}

Node* set_find(Set* set, int key) {
	return find_key(&set->tree_, key);
}

bool set_contains(Set* set, int key) {
	return (find_key(&set->tree_, key) != NULL);
}

int set_get_min(Set* set) {
	return get_min(set->tree_.root_)->key_;
}

int set_get_max(Set* set) {
	return get_max(set->tree_.root_)->key_;
}

int set_size(Set* set) {
	return set->tree_.num_nodes_;
}

bool set_is_empty(Set* set) {
	return set->tree_.num_nodes_ == 0;
}

Node* set_begin(Set* set) {
	return get_min(set->tree_.root_);
}

Node* set_end(Set* set) {
	return get_max(set->tree_.root_);
}

Node* set_next(Node* node) {
	return upper_bound(node);
}

void print_set(Set* set) {
	iterator itb = set_begin(set);
	for (; itb != NULL; itb = set_next(itb))
		printf("%d ", itb->key_);
	putchar('\n');
}

void clear_set(Set* set) {
	delete_bst(&set->tree_);
}
