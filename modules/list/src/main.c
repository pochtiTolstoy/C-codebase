#include <stdio.h>
#include "../include/tim_list.h"

//static int square_(int x) { return x * x; }

void print_arr(int arr[], int size) {
	for (int i = 0; i < size; ++i) {
		printf("%d ", arr[i]);
	}
	putchar('\n');
}

int main(void) {
	List list;
	init_list(&list);

	int arr[] = { 2, 10, 1, 11, 0, -1, -2, -3 };
	int size = sizeof(arr) / sizeof(arr[0]);
	create_from_array(&list, arr, size);
	print_list(&list);

#if 0
	print_arr(arr, size);	
	merge_sort(arr, 0, size - 1);
	print_arr(arr, size);	
#endif

	sort_list(&list);
	print_list(&list);
	enqueue(&list, 1000);
	print_list(&list);
	pop(&list);
	print_list(&list);
	push(&list, 100);
	print_list(&list);
	sort_list(&list);
	print_list(&list);
	free_list(&list);
	return 0;
}
