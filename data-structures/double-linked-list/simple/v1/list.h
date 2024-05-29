#ifndef LIST_H_
#define LIST_H_

#include <stdbool.h>
#define TSIZE 5
#define SSIZE 129

typedef char* Item;

typedef struct node {
  Item item;
  struct node* prev;
  struct node* next;
} Node;

typedef struct list {
  Node* head;
  unsigned int items;
} List;

void init_list(List*);
bool is_empty(const List*);
bool is_full(const List*);
unsigned int item_count(const List*);
Node* insert(List*, const Item); //O(1)
Node* find(const List*, const Item); //O(n)
bool delete_item(List*, const Item); //O(n) + O(1)
bool pop(List*, Item);
void traverse(const List*, void (*pf)(Item item));
void empty_the_list(List*);

#endif /* LIST_H_ */
