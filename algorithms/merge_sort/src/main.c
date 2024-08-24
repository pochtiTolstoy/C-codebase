#include <stdio.h>
#include "../include/merge_sort.h"

/*
void qsort(void *base, size_t nmemb, size_t size, 
	int (*compar)(const void *, const void *));
*/

int compare_ints(const void* a, const void* b)
{
	if (*(int*)a < *(int*)b) return -1;
	if (*(int*)a > *(int*)b) return  1;
	return 0;
}

int compare_double(const void *a, const void *b) 
{
	if (*(double*)a < *(double*)b) return -1;
	if (*(double*)a > *(double*)b) return  1;
	return 0;
	//return *(double*)a - *(double*)b;
}


void print_arr_int(int* arr, size_t size)
{
	for (size_t i = 0; i < size; ++i)
		printf("%d ", arr[i]);
	putchar('\n');
}

void print_arr_double(double* arr, size_t size)
{
	for (size_t i = 0; i < size; ++i)
		printf("%.2f ", arr[i]);
	putchar('\n');
}

int main(void) {
	int arr[] = { 
		100, 200, 1, 2, -50, 20, 0, 0, 2,
		25, 75, 5, 10, -10, 10, 100, 1, 150
	};

	const size_t size = sizeof(arr) / sizeof(arr[0]);
	print_arr_int(arr, size);
	merge_sort(arr, size, sizeof(int),
			compare_ints);
	print_arr_int(arr, size);


	double arr_real[] = {
		1.23, 3.24, 0.2, 0.11, 0.13, 0.14, -0.1, -0.11,
		100.22, 200.35, 0.15, 300, -5
	};
	const size_t size_real = 
		sizeof(arr_real) / sizeof(arr_real[0]);
	print_arr_double(arr_real, size_real);
	merge_sort(arr_real, size_real, sizeof(double),
			compare_double);
	print_arr_double(arr_real, size_real);

	return 0;
}
