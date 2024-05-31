#include "../include/tim_list.h"

// Help static methods
static void check_pop(const List* list) {
	if (!is_list_ready(list)) {
		fprintf(stderr, "List is not ready for pop. Abort.\n");
		abort();
	}
	if (is_list_empty(list)) {
		fprintf(stderr, "List is empty for pop method. Abort.\n");
		abort();
	} }

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

static void check_rear_pointer(const List* list) {
	if (list->rear_ == NULL) {
		fprintf(stderr, "Rear pointer is NULL. Abort.\n");
		abort();
	}
}

static void check_rear_correctness(const List* list) {
	if (list->rear_->next_ != list->tail_) {
		fprintf(stderr, "Rear pointer is Invalid. Abort.\n");
		abort();
	}
}

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
	list->rear_ = NULL;
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
	list->rear_ = (get_list_size(list) == 0) ? temp : list->rear_;

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

	// set pointers
	list->rear_ = (get_list_size(list) == 1) ? NULL : list->rear_;

	// change list data
	dec_size(list);

	return key;
}

// Push node to the end
void enqueue(List* list, int key) {
	if (get_list_size(list) == 0) {
		push(list, key);
		return;
	}
	if (!is_list_ready(list)) return;
	if (is_list_full(list)) return;

	// system inner check
	check_node_number(list);
	check_rear_pointer(list);
	check_rear_correctness(list);

	// allocation
	Node* temp = (Node*) malloc(sizeof(Node));
	check_node_alloc(temp);

	// init values
	temp->key_ = key;

	// set pointers
	temp->next_ = list->rear_->next_;
	list->rear_->next_ = temp;	
	list->rear_ = temp;

	// change list data
	inc_size(list);
}

int dequeue(List* list) {
	return pop(list);	
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
	list->rear_ = NULL;

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


Node* movenexttofront(List* list, const Node* prev_node) {
	Node* list_prev_node;
	if (!(list_prev_node = find_node(list, prev_node))) 
		return NULL;
	if (list_prev_node == list->rear_) 
		return NULL;
	// 1. List contains at least two nodes
	// 2. Given node in list and next node is valid
	
	list->rear_ = (list_prev_node->next_ == list->rear_) ? list_prev_node : list->rear_;
	Node* temp = list_prev_node->next_->next_;
	list_prev_node->next_->next_ = list->head_->next_;
	list->head_->next_ = list_prev_node->next_;
	list_prev_node->next_ = temp;

	return list->head_->next_;
}

/*
Node* exchangenext(List* list, const Node* u, const Node* v) {
	//////////////////////////////////////////////
	Node* list_u;
	Node* list_v;
	if (u == v) return NULL;
	if (!(list_u = find_node_ht(list, u))) return NULL;
	if (!(list_v = find_node_ht(list, v))) return NULL;
	if (list_u == list->tail_ || list_v == list->tail_)
		return NULL;
	if (list_u->next_)
}
*/

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
	return list->size_ == MAX_SIZE_LIST;
}

Node* find_node(const List* list, const Node* node) {
	Node* ptr = list->head_->next_;

	// only tail has this property
	while (ptr != ptr->next_) {
		if (ptr == node) return ptr;
		ptr = ptr->next_;
	}

	return NULL;
}

Node* find_node_ht(const List* list, const Node* node) {
	Node* ptr = list->head_;

	// only tail has this property
	while (ptr != ptr->next_) {
		if (ptr == node) return ptr;
		ptr = ptr->next_;
	}

	// check tail
	return (ptr == node) ? ptr : NULL;
}

Node* find_key(const List* list, int key) {
	Node* ptr = list->head_->next_;

	// only tail has this property
	while (ptr != ptr->next_) {
		if (ptr->key_ == key) return ptr;
		ptr = ptr->next_;
	}

	return NULL;
}

Node* find_key_ht(const List* list, int key) {
	Node* ptr = list->head_;

	// only tail has this property
	while (ptr != ptr->next_) {
		if (ptr->key_ == key) return ptr;
		ptr = ptr->next_;
	}

	// check tail
	return (ptr->key_ == key) ? ptr : NULL;
}

int get_list_size(const List* list) {
	return list->size_;
}

int get_list_capacity(void) {
	return MAX_SIZE_LIST;
}

bool is_list_ready(const List* list) {
	return (NULL != list->head_ && NULL != list->tail_);
}
