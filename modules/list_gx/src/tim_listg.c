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

static void print_void(Node* node) {
  printf("%p\n", node->key_.void_t);
}

static void print_pair(Node* node) {
  Pair* pt = &node->key_.pair;
  vtype_pair_t* type = &pt->key_type_;
  value_pair_t* elem = &pt->key;
  putchar('[');
  for (int i = 0; i < 2; ++i) {
    switch (*type) {
      case PDECIMAL:
        printf("%ld", (*elem).decimal);
        break;
      case PREAL:
        printf("%.2f", (*elem).real);
        break;
      case PSTRING:
        printf("%s", (*elem).string);
        break;
      default:
        abort();
    }
    (i == 0) ? printf(", ") : printf("],\n");
    type = &pt->value_type_;
    elem = &pt->value;
  }
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

static List* set_key_type_(List* list, const char* format) 
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
    case 'p':
      list->type_ = PAIR_ELEM;
      break;
    case 'v':
      list->type_ = VOID_ELEM;
      break;
		default: 
			return NULL;	
	}
  return list;
}

static void
init_list_union_(value_list_t* value, vtype_list_t type) 
{
  switch (type) {
    case DECIMAL_ELEM:
      (*value).decimal = 0;
      break;
    case REAL_ELEM:
      (*value).real = 0;
      break;
    case STRING_ELEM:
      (*value).string = NULL;
      break;
    default:
      fprintf(stderr, "Unknown type of list. Abort.");
  }
}

static Node* 
set_default_value_node_(Node* node, vtype_list_t type) 
{
	if (NULL == node) return NULL;
  switch (type) {
    case PAIR_ELEM:
      /*
      init_pair_union_(&node->key_.pair.key,   node->key_.pair.key_type_);
      init_pair_union_(&node->key_.pair.value, node->key_.pair.value_type_);
      */
      break;
    case VOID_ELEM:
      node->key_.void_t = NULL;
      break;
    default:
      init_list_union_(&node->key_, type);
  }
	return node;
}

static bool 
compare_decimal(value_list_t* n1, value_list_t* n2) 
{
  return ((*n1).decimal == (*n2).decimal);
}

static bool 
compare_real(value_list_t* n1, value_list_t* n2) 
{
  return ((*n1).real == (*n2).real);
}

static bool 
compare_strings(value_list_t* n1, value_list_t* n2) 
{
  return (strcmp((*n1).string, (*n2).string) == 0);
}

static bool
compare_voids(value_list_t* n1, value_list_t* n2) {
  return ((*n1).void_t == (*n2).void_t);
}

static bool
compare_pair(value_list_t* n1, value_list_t* n2)
{
  Pair* p1 = &((*n1).pair);
  Pair* p2 = &((*n2).pair);
  if ((*p1).key_type_ != (*p2).key_type_) {
    fprintf(stderr, "Incomparable types of pairs. Abort.\n");
    abort();
  }
  switch ((*p1).key_type_) {
    case PDECIMAL:
      return (p1->key.decimal == p2->key.decimal);
      break;
    case PREAL:
      return (p1->key.real == p2->key.real);
      break;
    case PSTRING:
      return (strcmp(p1->key.string, p2->key.string) == 0);
      break;
    default:
      fprintf(stderr, "Wrong pair type. Abort.\n");
      abort();
  }
  return false;
}

Node* init_list(List* list, const char* format) 
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
			temp->key_.string = va_arg(factor, char*);
			break;
    case PAIR_ELEM:
      temp->key_.pair = va_arg(factor, Pair);
      break;
    case VOID_ELEM:
      temp->key_.void_t = va_arg(factor, void*);
      break;
		default:
			fprintf(stderr, "Wrong type in list. Abort.");
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
    case PAIR_ELEM:
      ptr_print = print_pair;
      break;
    case VOID_ELEM:
      printf("print_list can't infer type from void*.\n");
      ptr_print = print_void;
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

Node* find_key(const List* list, ...) {
  if (is_list_empty(list)) return NULL;
  Node* ptr = list->head_->next_;
  Comparator compare = NULL;

  va_list arg;
  va_start (arg, list);
  value_list_t temp;
  char key_literal = '0';
  Pair temp_pair;
  char flag[2] = "xd";

  switch (list->type_) {
    case DECIMAL_ELEM: 
      compare = compare_decimal;
      temp.decimal = va_arg(arg, int64_t);
      break;
    case REAL_ELEM:
      compare = compare_real;
      temp.real = va_arg(arg, double);
      break;
    case STRING_ELEM:
      compare = compare_strings;
      temp.string = va_arg(arg, char*);
      break;
    case VOID_ELEM:
      compare = compare_voids;
      temp.void_t = va_arg(arg, void*);
      break;
    case PAIR_ELEM:
      compare = compare_pair;
      Node* first_node = list->head_->next_;
      switch (first_node->key_.pair.key_type_) {
        case PDECIMAL:
          temp.decimal = va_arg(arg, int64_t);
          key_literal = 'd';
          break;
        case PREAL:
          temp.real = va_arg(arg, double);
          key_literal = 'f';
          break;
        case PSTRING:
          temp.string = va_arg(arg, char*);
          key_literal = 's';
          break;
      }
      flag[0] = key_literal;
      switch (key_literal) {
        case 'd':
          init_pair(&temp_pair, flag, temp.decimal, -1);
          break;
        case 'f':
          init_pair(&temp_pair, flag, temp.real, -1);
          break;
        case 's':
          init_pair(&temp_pair, flag, temp.string, -1);
          break;
        default:
          break;
      }
      temp.pair = temp_pair;
      break;
    default:
      fprintf(stderr, "Wrong list type to compare. Abort.");
      abort();
  }

  while (ptr != ptr->next_) {
    if (compare(&ptr->key_, &temp))
      return ptr;
    ptr = ptr->next_;
  }
  return NULL;
}

void init_pair(Pair* pair, const char* format, ...)
{
  va_list factor; 
  va_start(factor, format);
  vtype_pair_t* pt = &pair->key_type_;
  value_pair_t* pv = &pair->key;
  for (; *format != '\0'; ++format) {
    switch (*format) {
      case 'd': case 'i':
        (*pt) = PDECIMAL;
        (*pv).decimal = va_arg(factor, int64_t);
        break;
      case 'r': case 'f':
        (*pt) = PREAL;
        (*pv).real = va_arg(factor, double);
        break;
      case 's':
        (*pt) = PSTRING;
        (*pv).string = va_arg(factor, char*);
        break;
    }
    pt = &pair->value_type_;
    pv = &pair->value;
  }
}
