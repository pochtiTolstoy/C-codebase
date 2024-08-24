#include "../include/merge_sort.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef int (*cmp_predicate)(const void*, const void*);

typedef struct s_merge_data {
  void *base;
  void *buf;
  const cmp_predicate compare;
  const size_t nmemb;
  const size_t size;
} s_merge_data;

static bool check_alloc_(void *ptr) {
  if (ptr != NULL) return true;
  fprintf(stderr, "Error. Bad allocation.\n");
  return false;
}

static void merge_(
    size_t l, size_t m, size_t r,
    s_merge_data* md
) {
  size_t k = 0;
  size_t i = l;
  size_t j = m + 1;
  size_t elems = r - l + 1;

  while (i <= m && j <= r)
    /* buf[k++] = (arr[i] < arr[j]) ? arr[i++] : arr[j++]; */
    (md->compare(md->base + i * md->size, md->base + j * md->size) <= 0) 
      ? memcpy(md->buf + k++ * md->size, md->base + i++ * md->size, md->size)
      : memcpy(md->buf + k++ * md->size, md->base + j++ * md->size, md->size)
      ;

  while (i <= m) /* buf[k++] = arr[i++]; */ 
    memcpy(md->buf + k++ * md->size, md->base + i++ * md->size, md->size);

  while (j <= r) /* buf[k++] = arr[j++]; */
    memcpy(md->buf + k++ * md->size, md->base + j++ * md->size, md->size);

  for (size_t idx = 0; idx < elems; ++idx) /* copy sorted chunck */
    memcpy(md->base + (l + idx) * md->size, md->buf + idx * md->size, md->size); 
}

static void merge_sort_(
    size_t l, size_t r,
    s_merge_data* merge_data
) {
  if (l >= r) return;
  size_t m = l + (r - l) / 2;
  merge_sort_(l, m, merge_data);
  merge_sort_(m + 1, r, merge_data);
  merge_(l, m, r, merge_data);
}

void merge_sort(
    void *base, size_t nmemb, size_t size,
		int (*compar)(const void*, const void*)
) {
  size_t l = 0;
  size_t r = nmemb - 1;
  void *buf = malloc(size * nmemb);
  s_merge_data merge_data = {
    .base = base, .buf = buf, .compare = compar,
    .nmemb = nmemb, .size = size
  };

  if (!check_alloc_(buf)) return;

  merge_sort_(l, r, &merge_data);
  free(buf);
}
