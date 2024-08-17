#include <stdio.h>
#include <stdlib.h>
#include "vec.h"

int main(void) {
  printf("Hello world!\n");
  const char* buf[] = {
    "Hello,", "my ", "name ", "is ", "Timur.",
    "I am ", "very ", "busy.", "What ", "do ",
    "you ", "want ", "from ", "me?"
  };
  const size_t size = sizeof(buf) / sizeof(buf[0]);
  Vec v;
  init_vec(&v, 2);
  for (size_t idx = 0; idx < size; ++idx)
    append_vec(&v, ((Pair) { 
      .key = buf[idx], .value = rand() % 10
    }));
  for (size_t idx = 0; idx < v.size; ++idx)
    printf("|%s: %zu|\n", 
        v.data[idx].key, v.data[idx].value);
  delete_vec(&v);
  return 0;
}
