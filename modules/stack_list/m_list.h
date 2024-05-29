// list module
#ifndef LIST_H_
#define LIST_H_

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

typedef struct Node {
  int key_;
  struct Node* next_;
} Node;

typedef struct List {
  Node* head_;
  Node* tail_;
  int size_;
} List;

// General methods
void init_list(List*);
void push(List*, int);
int pop(List*);

// deallocating elements in list without head and tail.
void clear_list(List*);

// all elements are deallocated including head and tail.
// list pointer itself is not NULL.
void free_list(List*);

// User methods
void print_list(const List*);
bool is_list_ready(const List*);
bool is_list_empty(const List*);
bool is_list_full(const List*);
int get_list_capacity(void);
int get_list_size(const List*);

// Help static methods
static void check_node_alloc(const Node*);
static void check_node_number(const List*);
static void inc_size(List*);
static void dec_size(List*);
static void check_clear_method(const List*);
static void check_pop(const List*);


// realization
// ====================================================================

static const int MAX_SIZE = 100000;

// General methods
void init_list(List* list) {
	// init list fields
  list->size_ = 0;

	// allocation
  list->head_ = (Node*) malloc(sizeof(Node));
	check_node_alloc(list->head_);
  list->tail_ = (Node*) malloc(sizeof(Node));
	check_node_alloc(list->tail_);

	// init values
  list->head_->key_ = 0;
  list->tail_->key_ = 0;

	// set pointers
  list->head_->next_ = list->tail_;
  list->tail_->next_ = list->tail_; // only this node has this property
}

void push(List* list, int key) {
	if (!is_list_ready(list)) return;
	if (is_list_full(list)) return;

	// system inner check
	check_node_number(list);

	// allocation
	Node* temp = (Node*) malloc(sizeof(Node));
	check_node_alloc(temp);

	// init values
	temp->key_ = key;

	// set pointers
	temp->next_ = list->head_->next_;
	list->head_->next_ = temp;

	// change list data
	inc_size(list);
}

int pop(List* list) {
	check_pop(list);
	// store data in temp for deallocation
	Node* temp = list->head_->next_;
	int key = temp->key_;

	// detach node
	list->head_->next_ = temp->next_;

	// deallocation
	free(temp);

	// change list data
	dec_size(list);

	return key;
}


void clear_list(List* list) { if (!is_list_ready(list)) return;
	check_node_number(list);
	Node* temp = NULL;
	
	// while some elements appear between head and tail
	while (list->head_->next_ != list->tail_) {
		temp = list->head_->next_;		
		list->head_->next_ = temp->next_;
		free(temp);
		dec_size(list);
	}

	// should be 0 elements
	check_clear_method(list);
}

void free_list(List* list) {
	clear_list(list);
	free(list->head_);
	free(list->tail_);
	list->head_ = NULL;
	list->tail_ = NULL;
}

// User methods

void print_list(const List* list) {
	if (!is_list_ready(list) || is_list_empty(list)) return;	
	Node* temp = list->head_->next_;
	while (temp != list->tail_) {
		printf("%d ", temp->key_);
		temp = temp->next_;
	}
	putchar('\n');
}

bool is_list_empty(const List* list) {
  return list->size_ == 0;
}

bool is_list_full(const List* list) {
	return list->size_ == MAX_SIZE;
}

int get_list_size(const List* list) {
	return list->size_;
}

int get_list_capacity(void) {
	return MAX_SIZE;
}

bool is_list_ready(const List* list) {
	return (NULL != list->head_ && NULL != list->tail_);
}

// Help static methods
static void check_pop(const List* list) {
	if (!is_list_ready(list)) {
		fprintf(stderr, "List is not ready for pop. Abort.\n");
		abort();
	}
	if (is_list_empty(list)) {
		fprintf(stderr, "List is empty for pop method. Abort.\n");
		abort();
	}
}

static void check_node_alloc(const Node* node) {
	if (NULL == node) {
		fprintf(stderr, "%s\n", "List bad allocation. Abort.\n");
		abort();
	}
}

static void check_node_number(const List* list) {
	if (list->size_ < 0) {
		fprintf(stderr, "%s\n", "Incorrect number of nodes in list. Abort.\n");
		abort();
	}
}

static void inc_size(List* list) {
	if (++list->size_ <= 0) {
		fprintf(stderr, "%s\n", "Incorrect number of nodes in list"
				" after increment. Abort.");	
		abort();
	}
}

static void dec_size(List* list) {
	if (--list->size_ < 0) {
		fprintf(stderr, "%s\n", "Incorrect number of nodes in list"
				" after decrement. Abort.");	
		abort();
	}
}

static void check_clear_method(const List* list) {
	if (list->size_ != 0) {
		fprintf(
			stderr,
			"Incorrect number of nodes in list after clear method.\n"
			"Expected: 0 elements, met: %d.\n"
			"Abort.\n", list->size_
		);
		abort();
	}
}

#endif /* LIST_H_ */
