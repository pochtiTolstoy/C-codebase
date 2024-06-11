#include "../include/tim_dl_list_s.h"

static void check_node_alloc(const Node* node) {
	if (NULL == node) {
		fprintf(stderr, "%s\n", "List bad allocation. Abort.\n");
		abort();
	}
}

static void check_str_alloc(const char* str) {
	if (NULL == str) {
		fprintf(stderr, "String bad allocation. Abort.\n");
		abort();
	}
}

static void check_clear_method(const List* list) {
	if (list->size_ == 0
			&& list->head_->prev_ == list->head_
			&& list->head_->next_ == list->tail_
			&& list->tail_->next_ == list->tail_
			&& list->tail_->prev_ == list->head_)
		return;
	fprintf(stderr, "Invalid list after clear method. Abort.\n");
	abort();
}

void init_list(List* list) {
	list->size_ = 0;
	list->head_ = (Node*)	malloc(sizeof(Node));
	check_node_alloc(list->head_);
	list->tail_ = (Node*) malloc(sizeof(Node));
	check_node_alloc(list->tail_);

	list->head_->str_ = NULL;
	list->tail_->str_ = NULL;

	list->head_->next_ = list->tail_;
	list->head_->prev_ = list->head_;
	list->tail_->next_ = list->tail_;
	list->tail_->prev_ = list->head_;
}

Node* push(List* list, const char* str) {
	if (is_list_full(list)) return NULL;
	Node* temp = (Node*) malloc(sizeof(Node));
	check_node_alloc(temp);

	temp->str_ = strdup(str);
	check_str_alloc(temp->str_);

	temp->next_ = list->head_->next_;
	temp->prev_ = list->head_;
	list->head_->next_ = temp;
	temp->next_->prev_ = temp;
	++list->size_;
	return temp;
}

void pop(List* list) {
	if (is_list_empty(list)) return;
	Node* temp = list->head_->next_;
	list->head_->next_ = temp->next_;
	temp->next_->prev_ = list->head_;
	free(temp->str_);
	free(temp); // string is alive

	--list->size_;
}

char* pop_str(List* list) {
	if (is_list_empty(list)) return NULL;
	Node* temp = list->head_->next_;
	char* str = temp->str_;
	list->head_->next_ = temp->next_;
	temp->next_->prev_ = list->head_;

	free(temp); // string is alive

	--list->size_;
	return str;
}

Node* insertafter_f(List* list, Node* node, const char* str) {
	if (is_list_full(list))	return NULL;
	if (node == list->tail_) return NULL;
	Node* temp = (Node*) malloc(sizeof(Node));
	check_node_alloc(temp);

	temp->str_ = strdup(str);

	temp->next_ = node->next_;
	temp->prev_ = node;
	node->next_ = temp;
	temp->next_->prev_ = temp;

	++list->size_;
	return temp;
}

Node* find_str(List* list, const char* str) {
	Node* temp = list->head_->next_;
	while (temp != temp->next_) {
		if (strcmp(temp->str_, str) == 0) 
			return temp;
		temp = temp->next_;
	}
	return NULL;
}

Node* delete_node_f(List* list, Node* node) {
	Node* temp = node->prev_;
	node->prev_->next_ = node->next_;
	node->next_->prev_ = node->prev_;
	free(node->str_);
	free(node);
	--list->size_;
	return temp;
}

void clear_list(List* list) {
	Node* temp = NULL;
	while (list->head_->next_ != list->tail_) {
		temp = list->head_->next_;
		list->head_->next_ = temp->next_;
		free(temp->str_);
		free(temp);

		--list->size_;
	}
	list->tail_->prev_ = list->head_;
	check_clear_method(list);
}

void free_list(List* list) {
	clear_list(list);
	free(list->head_);
	free(list->tail_);
	list->head_ = NULL;
	list->tail_ = NULL;
}

bool is_list_full(const List* list) {
	return list->size_ == MAX_SIZE_LIST;
}

bool is_list_empty(const List* list) {
	return list->size_ == 0;
}

void print_node(Node* node) {
	printf("str: %s\n", node->str_);
}

void traverse(List* list, void (*pf)(Node*)) {
	Node* temp = list->head_->next_;	
	while (temp != temp->next_) {
		(*pf)(temp);
		temp = temp->next_;
	}
}

void print_list(List* list) {
	traverse(list, print_node);
}
