#include "../include/util.h"

void merge(int arr[], u32 l, u32 m, u32 r, int* temp) {
  u32 i = l;
  u32 j = m + 1;
  int k = 0;
  u32 size = r - l + 1;
  while (i <= m && j <= r)
    temp[k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
  while (i <= m)
    temp[k++] = arr[i++];
  while (j <= r)
    temp[k++] = arr[j++];
  for (u32 ii = 0; ii < size; ++ii)
    arr[l + ii] = temp[ii];
}

void merge_sort(int arr[], u32 l, u32 r, int* temp) {
  if (l < r) {
    u32 m = l + (r - l) / 2;
    merge_sort(arr, l, m, temp);
    merge_sort(arr, m + 1, r, temp);
    merge(arr, l, m, r, temp);
  }
}

int* sort(int arr[], u32 size) {
  int* temp = (int*) malloc(sizeof(int) * size);
  merge_sort(arr, 0, size - 1, temp);
  free(temp);
	return arr;
}

bool cmp_arrays(int in[], int out[], u32 size) {
  for (u32 i = 0; i < size; ++i)
    if (in[i] != out[i]) 
      return false;
  return true;
}

void print_array(int arr[], u32 size) {
  for (u32 i = 0; i < size; ++i)
    printf("%d ", arr[i]);
  putchar('\n');
}

bool is_array_sorted(int arr[], u32 size) {
	for (u32 i = 1; i < size; ++i)
		if (arr[i] < arr[i - 1])
			return false;
	return true;
}

void fill_array_rand(int arr[], u32 size) {
	for (u32 i = 0; i < size; ++i) 
    arr[i] = rand() % 1000;
}

void fill_array_incorder(int arr[], u32 size) {
  fill_array_rand(arr, size);
  sort(arr, size);
}
