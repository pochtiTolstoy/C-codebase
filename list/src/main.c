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
	int arr[] = { 1, 2, 3 };
	int size = sizeof(arr) / sizeof(arr[0]);
	print_list(create_from_array(&list, arr, size));
	print_node(get_middle_node(&list));
	free_list(&list);
	return 0;
}
