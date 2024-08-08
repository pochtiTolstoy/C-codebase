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
  free_list(&list);

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

  free_list(&list_str);

// PAIR DECIMAL-STRING ===================================
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

  if (find_key(&list_pair1, 200)) {
    printf("Key 200 is found\n");
  }
  Pair temp;
  temp = pop(&list_pair1).pair;
  printf("temp: [%ld, %s]\n", temp.key.decimal, temp.value.string);

  print_list(&list_pair1);

  free_list(&list_pair1);

// PAIR STRING-DOUBLE =========================================
  List list_pair2;
  init_list(&list_pair2, "p");
  Pair s1, s2, s3, s4, s5;
  init_pair(&s1, "sf", "Artur", 5.0);
  init_pair(&s2, "sf", "Bob", 3.2);
  init_pair(&s3, "sf", "Bill", 4.4);
  init_pair(&s4, "sf", "Cesar", 4.9);
  init_pair(&s5, "sf", "Dima", 2.8);
  push(&list_pair2, s1);
  push(&list_pair2, s2);
  push(&list_pair2, s3);
  push(&list_pair2, s5);
  print_list(&list_pair2);
  if (find_key(&list_pair2, "Dima")) {
    Pair temp = pop(&list_pair2).pair;
    printf("Student with bad score: %s - %f\n", temp.key.string, temp.value.real);
  } else {
    printf("Dima is not in list.\n");
  }

  push(&list_pair2, s4);
  print_list(&list_pair2);

  free_list(&list_pair2);
	return 0;
}
