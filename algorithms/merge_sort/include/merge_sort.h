#ifndef MERGE_SORT_H_
#define MERGE_SORT_H_

#include <stddef.h>

/*
void qsort(void *base, size_t nmemb, size_t size, 
	int (*compar)(const void *, const void *));
*/

void merge_sort(void *base, size_t nmemb, size_t size,
		int (*compar)(const void*, const void*));

#endif /* MERGE_SORT_H_ */
