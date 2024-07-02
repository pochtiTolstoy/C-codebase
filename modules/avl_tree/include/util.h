#ifndef UTIL_H_
#define UTIL_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned int u32;

void merge(int [], u32, u32, u32, int*);
void merge_sort(int [], u32, u32, int*);
int* sort(int [], u32);
bool cmp_arrays(int [], int [], u32);
void print_array(int [], u32);
void fill_array_rand(int [], u32);
void fill_array_incorder(int [], u32);

#endif /* UTIL_H_ */
