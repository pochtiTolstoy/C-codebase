#include "../include/tim_list.h"

// Help static methods
static void swap_neighbours_pointers_(Node* u, Node* v) {
	u->next_ = v->next_;
	v->next_ = v->next_->next_;
	u->next_->next_ = v;
}

static Node* swap_neighbours_next_(List* list, Node* u, Node* v) {
	if (u->next_ == v) {
		if (v->next_ == list->rear_) list->rear_ = u->next_;
		swap_neighbours_pointers_(u, v);
	} else if (v->next_ == u) {
		if (u->next_ == list->rear_) list->rear_ = v->next_;
		swap_neighbours_pointers_(v, u);
	} else return NULL;
	return u;
}

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

static Node* set_rear_pointer_(List* list) {
	if (list->rear_ == NULL) return NULL;
	if (list->rear_->next_ == list->tail_) return list->rear_;
	list->rear_ = NULL;
	Node* ptr = list->head_->next_;
	while (ptr != ptr->next_) {
		list->rear_ = ptr;	
		ptr = ptr->next_;
	}
	return list->rear_;
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

Node* push(List* list, int key) {
	if (!is_list_ready(list)) return NULL;
	if (is_list_full(list)) return NULL;

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

	check_rear_correctness(list);

	return temp;
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


void clear_list(List* list) { 
	if (!is_list_ready(list)) return;
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
	check_rear_correctness(list);
	Node* temp = list_prev_node->next_->next_;
	list_prev_node->next_->next_ = list->head_->next_;
	list->head_->next_ = list_prev_node->next_;
	list_prev_node->next_ = temp;

	return list->head_->next_;
}

Node* exchangenext(List* list, const Node* u, const Node* v) {
	Node* node_u;
	Node* node_v;

	// Routine to achieve safety
	if (u == v) return NULL;
	if (!(node_u = find_node_ht(list, u))) return NULL;
	if (!(node_v = find_node_ht(list, v))) return NULL;
	if (node_u == list->tail_ || node_v == list->tail_)
		return NULL;
	if (node_u->next_ == list->tail_ || node_v->next_ == list->tail_)
		return NULL;

	// Check if nodes are neighbours
	if (swap_neighbours_next_(list, node_u, node_v)) 
		return node_u;

	// Set rear pointer
	if (node_u->next_ == list->rear_) list->rear_ = node_v->next_;
	else if (node_v->next_ == list->rear_) list->rear_ = node_u->next_;
	
	// If nodes are not neighbours, then start main algorithm
	Node* p1 = node_u->next_;	
	Node* p2 = node_v->next_->next_;
	node_u->next_ = node_v->next_;
	node_v->next_->next_ = p1->next_;
	node_v->next_ = p1;
	p1->next_ = p2;

	check_rear_correctness(list);

	return node_u;
}

bool compare_lists(const List* l1, const List* l2) {
	if (get_list_size(l1) != get_list_size(l2)) return false;
	Node* node_l1 = l1->head_->next_;
	Node* node_l2 = l2->head_->next_;
	while (node_l1 != node_l1->next_
			&& node_l2 != node_l2->next_) { // only tail has this property
		if (node_l1->key_ != node_l2->key_) return false;
		node_l1 = node_l1->next_;
		node_l2 = node_l2->next_;
	}
	return l1->rear_->next_ == l1->tail_ 
			&& l2->rear_->next_ == l2->tail_;
}

List* sort_list(List* list) {
	if (!is_list_valid(list)) return NULL;
	if (list->size_ < 2) return list;

	// Store keys of list in array
	int* arr = (int*) malloc(sizeof(int) * list->size_);
	Node* ptr = list->head_->next_;
	for (int i = 0; i < list->size_; ++i) {
		arr[i] = ptr->key_;
		ptr = ptr->next_;
	}
	
	merge_sort(arr, 0, list->size_ - 1);

	// Put sorted keys in list
	ptr = list->head_->next_;
	for (int i = 0; i < list->size_; ++i) {
		ptr->key_ = arr[i];
		ptr = ptr->next_;
	}

	// Deallocating
	free(arr);

	return list;	
}

Node* get_prev_node(const List* list, const Node* node) {
	Node* prev_node = list->head_;
	while (prev_node != prev_node->next_) { // only tail has this property
		if (prev_node->next_ == node) return prev_node;
		prev_node = prev_node->next_;
	}
	return NULL;
}

Node* insertafter(List* list, const Node* node, int key) {
	Node* list_node;	
	if (!is_list_ready(list)) return NULL;
	if (is_list_full(list)) return NULL;
	if (node == list->tail_) return NULL;
	if (!(list_node = find_node_ht(list, node))) return NULL;

	// system inner check
	check_node_number(list);

	// allocation
	Node* temp = (Node*) malloc(sizeof(Node));
	check_node_alloc(temp);

	if (list->rear_ == list_node) list->rear_ = temp;
	check_rear_correctness(list);

	// init values
	temp->key_ = key;

	// set pointers
	temp->next_ = list_node->next_;
	list_node->next_ = temp;

	// change list data
	inc_size(list);

	return temp;
}

Node* deletenext(List* list, const Node* node) {
	Node* list_node;
	Node* temp;
	if (!is_list_ready(list)) return NULL;
	if (!(list_node = find_node_ht(list, node))) return NULL;
	temp = list_node->next_;
	if (temp == list->tail_) return NULL;
	if (temp == list->rear_) list->rear_ = list_node;
	list_node->next_ = list_node->next_->next_;
	free(temp);

	dec_size(list);

	return list_node;
}

List* create_from_array(List* list, int arr[], int size) {
	if (size <= 0) return NULL;
	if (!is_list_ready(list)) return NULL;
	clear_list(list);
	for (int i = size - 1; i >= 0; --i) {
		push(list, arr[i]);
	}
	return list;
}

List* reverselist(List* list) {
	if (!is_list_ready(list)) return NULL;
	Node* p1;
	Node* p2;
	Node* p3;
	if (list->size_ < 2) return list;
	if (list->size_ == 2) {
		swap_neighbours_next_(list, list->head_, list->head_->next_);
		return list;
	}
	p1 = list->head_->next_;
	p2 = p1->next_;
	p3 = p2->next_;
	
	p1->next_ = list->tail_;
	list->head_->next_ = list->rear_;		

	// set rear pointer
	list->rear_ = p1;

	while (p3 != p3->next_) { // only tail has this property
		p2->next_ = p1;
		p1 = p2;
		p2 = p3;
		p3 = p3->next_;
	}
	p2->next_ = p1;

	return list;
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

void print_node(const Node* node) {
	if (node == NULL) return;
	printf("key: %d, next: %p\n", node->key_, node->next_);
}

bool is_list_empty(const List* list) {
  return list->size_ == 0;
}

bool is_list_full(const List* list) {
	return list->size_ == MAX_SIZE_LIST;
}

bool is_list_valid(const List* list) {
	if (list == NULL 
			|| list->head_ == NULL 
			|| list->tail_ == NULL
			|| list->tail_->next_ == NULL
			|| list->tail_->next_ != list->tail_
			|| list->size_ < 0
			|| list->head_->next_ == NULL)
		return false;

	if (list->head_->next_ == list->tail_
			&& list->size_ == 0
			&& list->rear_ == NULL)
		return true;

	Node* ptr = list->head_->next_;
	int count_elems = 0;
	while (ptr != ptr->next_ && count_elems < MAX_SIZE_LIST) {
		++count_elems;
		ptr = ptr->next_;
	}

	if (ptr == list->tail_
			&& count_elems == list->size_
			&& list->rear_->next_ == list->tail_)
		return true;

	return false;
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

Node* find_at(const List* list, int index) {
	if (index < 0 || index >= get_list_size(list)) return NULL;
	Node* ptr = list->head_->next_;
	while (index--) ptr = ptr->next_;
	return ptr;
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

// Code which should be in other files in future
void merge(int arr[], int l, int m, int r) {
	int i = l;
	int j = m + 1;
	int temp_size = r - l + 1;
	int k = 0;
	int* temp = (int*) malloc(sizeof(int) * temp_size);
	while (i <= m && j <= r)
		temp[k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
	while (i <= m) temp[k++] = arr[i++];
	while (j <= r) temp[k++] = arr[j++];
	for (int idx = 0; idx < temp_size; ++idx)
		arr[l + idx] = temp[idx];
	free(temp);
}

void merge_sort(int arr[], int l, int r) {
	if (l < r) {
		int m = l + (r - l) / 2;
		merge_sort(arr, l, m);
		merge_sort(arr, m + 1, r);
		merge(arr, l, m, r);
	}
}
