#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"

void init_list(List* plist) {
  plist->head = NULL;
  plist->items = 0;
}

bool is_empty(const List* plist) {
  return plist->head == NULL;
}

bool is_full(const List* plist) {
  return plist->items == TSIZE;
}

unsigned int item_count(const List* plist) {
  return plist->items;
}

Node* insert(List* plist, const Item item) {
  if (is_full(plist)) {
    printf("Error, list is full! Item: %s\n", item);
    return NULL;
  }
  // alloc Node
  ++plist->items;
  Node* p_node = (Node*) malloc(sizeof(Node));
  // alloc string
  int len = strlen(item);
  p_node->item = (char*) malloc((len + 1) * sizeof(char));
  strcpy(p_node->item, item);
  p_node->item[len] = '\0';
  // rearrange pointers
  p_node->next = plist->head;
  if (plist->head != NULL)
    plist->head->prev = p_node;
  p_node->prev = NULL;
  plist->head = p_node;
  return p_node;
}

Node* find(const List* plist, const Item item) {
  Node* ptr = plist->head;
  while (ptr != NULL) {
    if (strlen(ptr->item) == strlen(item) 
        && strcmp(ptr->item, item) == 0)
      return ptr;
    ptr = ptr->next;
  }
  return NULL;
}

bool delete_item(List* plist, const Item item) {
  Node* ptr;
  if (!(ptr = find(plist, item)))
    return false;
  --plist->items;
  if (ptr->prev != NULL)
    ptr->prev->next = ptr->next;
  else
    plist->head = ptr->next;
  if (ptr->next != NULL)
    ptr->next->prev = ptr->prev;
  free(ptr->item);
  free(ptr);
  return true;
}

bool pop(List* plist, Item item) {
  if (plist->head == NULL)
    return false;
  --plist->items;
  Node* ptr = plist->head;
  if (ptr->next != NULL)
    ptr->next->prev = NULL;
  plist->head = ptr->next;
  strncpy(item, ptr->item, SSIZE);
  item[SSIZE - 1] = '\0';
  return true;
}

void empty_the_list(List* plist) {
  Node* ptr;
  while (plist->head != NULL) {
    ptr = plist->head; 
    plist->head = plist->head->next;
    free(ptr->item);
    free(ptr);
  }
  plist->items = 0;
}

void traverse(const List* plist, void (*pf)(Item item)) {
  Node* ptr = plist->head;
  while (ptr != NULL) {
    (*pf)(ptr->item);
    ptr = ptr->next;
  }
}
