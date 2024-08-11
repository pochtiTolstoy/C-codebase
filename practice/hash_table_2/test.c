#include <stdio.h>

int main(void) {
  int x[2] = {10, 20};
  int* p = x;
  int n = ++*p;
  for (int i = 0; i < 2; ++i) {
    printf("%d ", x[i]);
  }
  printf("\nnum = %d\n", n);
  printf("p = %d\n", *p);
  return 0;
}
