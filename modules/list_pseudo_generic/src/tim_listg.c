#include "../include/tim_listg.h"

static bool is_list_ready(const List* list) {
	return (NULL != list->head_ && NULL != list->tail_);
}

static void print_decimal(Node* node) {
  printf("%ld ", node->key_.decimal);  
}

static void print_double(Node* node) {
  printf("%f ", node->key_.real);  
}

static void print_string(Node* node) {
  printf("%s ", node->key_.string);  
}

static bool is_list_empty(const List* list) {
  return list->size_ == 0;
}

static bool is_list_full(const List* list) {
	return list->size_ == MAX_SIZE_LIST;
}

static void check_node_alloc(const Node* node) 
{
	if (NULL == node) {
		fprintf(stderr, "%s\n", "List bad allocation. Abort.\n");
		abort();
	}
}

static List* set_key_type_(List* list, const uint8_t* format) 
{
	if (NULL == format || NULL == list) 
		return NULL;

	switch (*format) {
		case 'd': case 'i': /* decimal */
			list->type_ = DECIMAL_ELEM; 
			break;
		case 'r': case 'f': /* real */
			list->type_ = REAL_ELEM;    
			break;
		case 's': /* string */
			list->type_ = STRING_ELEM;  
			break;
		default: 
			return NULL;	
	}
  return list;
}

static Node* set_default_value_node_(Node* node, vtype_list_t type) 
{
	if (NULL == node) return NULL;
	switch (type) {
		case DECIMAL_ELEM:
			node->key_.decimal = 0;
			break;
		case REAL_ELEM:
			node->key_.real = 0.0;
			break;
		case STRING_ELEM:
			node->key_.string = NULL;
			break;
		default:
			fprintf(stderr, "Unknown type of list element.");
			abort();
	}
	return node;
}

Node* init_list(List* list, const uint8_t* format) 
{
	if (NULL == set_key_type_(list, format))
		return NULL;

	list->size_ = 0;

	list->head_ = (Node*) malloc(sizeof(Node));
	check_node_alloc(list->head_);
  list->tail_ = (Node*) malloc(sizeof(Node));
	check_node_alloc(list->tail_);
	
	set_default_value_node_(list->head_, list->type_);
	set_default_value_node_(list->tail_, list->type_);

	list->head_->next_ = list->tail_;
	list->tail_->next_ = list->tail_;
	list->rear_ = NULL;

	return list->head_;
}

Node* push(List* list, ...)
{
	if (!is_list_ready(list)) return NULL;
	if (is_list_full(list))   return NULL;

	Node* temp = (Node*) malloc(sizeof(Node));
	check_node_alloc(temp);

  va_list factor;
  va_start(factor, list);
	switch (list->type_) {
		case DECIMAL_ELEM:
			temp->key_.decimal = va_arg(factor, int64_t);
			break;
		case REAL_ELEM:
			temp->key_.real = va_arg(factor, double);
			break;
		case STRING_ELEM:
			temp->key_.string = va_arg(factor, uint8_t*);
			break;
		default:
			fprintf(stderr, "Pushed wrong type in list. Abort.");
			abort();
	}
  va_end(factor);

	temp->next_ = list->head_->next_;
	list->head_->next_ = temp;
	list->rear_ = (list->size_ == 0) ? temp : list->rear_;

	++list->size_;

	return temp;
}

void print_list(const List* list) 
{
	if (!is_list_ready(list) || is_list_empty(list)) return;

	Node* temp = list->head_->next_;
  void (*ptr_print) (Node*) = NULL;

  switch (list->type_) {
    case DECIMAL_ELEM:
      ptr_print = print_decimal;
      break;
    case REAL_ELEM:
      ptr_print = print_double;
      break;
    case STRING_ELEM:
      ptr_print = print_string;
      break;
    default:
      fprintf(stderr, "Wrong list type to print. Abort.");
      abort();
  }

	while (temp != list->tail_) {
    (*ptr_print)(temp);
    temp = temp->next_;
	}
  putchar('\n');
}

void clear_list(List* list) 
{
  if (!is_list_ready(list)) return;
  Node* temp = NULL;

  while (list->head_->next_ != list->tail_) {
    temp = list->head_->next_;
    list->head_->next_ = temp->next_;
    free(temp);
    --list->size_;
  }

  assert(list->size_ == 0);

  list->rear_ = NULL;
}

void free_list(List* list)
{
  clear_list(list);
  free(list->head_);
  free(list->tail_);
  list->head_ = NULL;
  list->tail_ = NULL;
}

value_list_t pop(List* list)
{
  Node* temp = list->head_->next_;
  value_list_t key = temp->key_;
  
  list->head_->next_ = temp->next_;
  free(temp);

  list->rear_ = (list->size_ == 1) ? NULL : list->rear_;

  --list->size_;

  return key;
}

Node* find_node(const List* list, const Node* node) 
{
  Node* ptr = list->head_->next_;

  while (ptr != ptr->next_) {
    if (ptr == node) return ptr;
    ptr = ptr->next_;
  }
  return NULL;
}
