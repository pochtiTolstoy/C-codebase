#include <stdio.h>
#include "../include/tim_listg.h"

int main(void) {
	printf("Hello world!\n");

// DECIMAL =============================================
	List list;
  const char* str = "Hello, my name is Timur!";
	init_list(&list, "d");
  push(&list, 100);
  for (int i = 200; i <= 1000; i += 50) {
    push(&list, i);
  }
	print_list(&list);

  if (find_key(&list, 450)) 
    printf("Key was found!\n");
  else
    printf("Key is not found\n");

  int64_t elem = pop(&list).decimal; 
  printf("poped: %ld.\n", elem);
	print_list(&list);

// STRING =============================================
  List list_str;
  init_list(&list_str, "s");
  push(&list_str, str);
  push(&list_str, "This is very informative string.");
  push(&list_str, "I love you.");
  print_list(&list_str);
  if (find_key(&list_str, "I love you.")) {
    printf("String was found!\n");
  } else {
    printf("String is not found!\n");
  }
  printf("Poped str: %s\n", pop(&list_str).string);
  print_list(&list_str);

  if (find_key(&list_str, "I love you.")) {
    printf("String was found!\n");
  } else {
    printf("String is not found!\n");
  }

  free_list(&list);
  free_list(&list_str);

// PAIR KEY-STRING ===================================
  List list_pair1;
  init_list(&list_pair1, "p");
  Pair p1;
  init_pair(&p1, "ds", 10, "Hello I am string");

  Pair p2;
  init_pair(&p2, "ds", 50, "Where am I?");

  Pair p3;
  init_pair(&p3, "ds", 200, "It is rainy outside.");

  Pair p4;
  init_pair(&p4, "ds", 100, "123123 - cool number.");

  push(&list_pair1, p1);
  push(&list_pair1, p2);
  push(&list_pair1, p3);
  push(&list_pair1, p4);

  print_list(&list_pair1);

  free_list(&list_pair1);

	return 0;
}
