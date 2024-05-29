#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>

// TODO: 
// extern List* delbyid_list(List* list, size_t index);
// extern List* addbyid_list(List* list, size_t index, uint8_t* format, ...);
// extern _Bool elemin_list(List* list, uint8_t* format, ...); 

typedef enum {
  _INIT_ELEM,
  _DECIMAL_ELEM,
  _REAL_ELEM,
  _STRING_ELEM
} vtype_list_t;

typedef union {
  int64_t decimal;
  double real;
  uint8_t* string;
} value_list_t; // Выделяет одну область памяти для хранения разных типов

typedef struct List {
  vtype_list_t type;
  value_list_t value;
  struct List* next;
} List;

// List* list = new_list("drs", 5, 1.11, "Hello");
extern List* new_list(uint8_t* format, ...);
extern void free_list(List* list);
extern List* push_list(List* list, uint8_t* format, ...);
extern List* pop_list(List* list);
extern void print_list(List* list);

int main(void) {
  List* list = new_list("drs", 0, 1.25, "Hello world!");
  List* temp = push_list(list, "d", 123);
  // O(1)
  temp = push_list(temp, "ddd", 1, 102, 29);
  temp = push_list(temp, "d", 2);
  temp = push_list(temp, "d", 3);

  print_list(list);
  List* l1;
  while (list->next != NULL) {
    l1 = pop_list(list);    
    print_list(l1);
    free_list(l1);
  }
  print_list(list);
  free_list(list);

  return 0;
}

extern List* new_list(uint8_t* format, ...) {
  List* list = (List*) malloc(sizeof(List)); 
  List* list_ptr = list;
  list->type = _INIT_ELEM;
  list->next = NULL;
  value_list_t value;
  va_list factor;
  va_start(factor, format);
  while (*format) {
    switch (*format) {
      case 'd': case 'i': // decimal
        value.decimal = va_arg(factor, int64_t);
        list_ptr = push_list(list_ptr, "d", value.decimal);
        break;
      case 'r': case 'f': // real
        value.real = va_arg(factor, double);
        list_ptr = push_list(list_ptr, "r", value.real);
        break;
      case 's': // string
        value.string = va_arg(factor, uint8_t*);
        list_ptr = push_list(list_ptr, "s", value.string);
        break;
    }
    ++format;
  }
  va_end(factor);
  return list;
}

extern List* push_list(List* list, uint8_t* format, ...) {
  if (list == NULL) {
    fprintf(stderr, "list is null\n");
    return NULL;
  }
  while (list->next != NULL) {
    list = list->next;
  }
  value_list_t value;
  va_list factor;
  va_start(factor, format);
  while (*format) {
    switch (*format) {
      case 'd': case 'i': // decimal
        value.decimal = va_arg(factor, int64_t);
        list->next = (List*) malloc(sizeof(List));
        list = list->next;
        list->type = _DECIMAL_ELEM;
        list->value.decimal = value.decimal;
        list->next = NULL;
        break;
      case 'r': case 'f': // real
        value.real = va_arg(factor, double);
        list->next = (List*) malloc(sizeof(List));
        list = list->next;
        list->type = _REAL_ELEM;
        list->value.real = value.real;
        list->next = NULL;
        break;
      case 's': // string
        value.string = va_arg(factor, uint8_t*);
        list->next = (List*) malloc(sizeof(List));
        list = list->next;
        list->type = _STRING_ELEM;
        list->value.string = value.string;
        list->next = NULL;
        break;
    }
    ++format;
  }
  va_end(factor);
  return list;
}

extern List* pop_list(List* list) {

  if (list == NULL) {
    fprintf(stderr, "list is null\n");
    return NULL;
  }
  if (list->next == NULL) {
    return list;
  }
  List* prev_list = list;
  List* past_list = list->next;
  while (past_list->next != NULL) {
    prev_list = past_list;
    past_list = past_list->next;
  }
  prev_list->next = NULL;
  return past_list; // should be free
}

extern void print_list(List* list) {
  printf("[ ");
  if (list->type == _INIT_ELEM && list->next != NULL) {
    list = list->next;
  }
  while (list != NULL) {
    switch (list->type) {
      case _DECIMAL_ELEM:
        printf("%ld ", list->value.decimal);
        break;
      case _REAL_ELEM:
        printf("%lf ", list->value.real);
        break;
      case _STRING_ELEM:
        printf("\"%s\" ", list->value.string);
        break;
      default:
        printf("_INIT_ELEM ");
        break;
    }
    list = list->next;
  }
  printf("]\n");
}

extern void free_list(List* list) {
  List* list_ptr;
  while (list != NULL) {
    list_ptr = list;
    list = list->next;
    free(list_ptr);
  }
}
