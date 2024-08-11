#include "hash_table.h"
#include <stdio.h>

int main(void) 
{
  ht_hash_table* ht = ht_new();
  ht_del_hash_table(ht);
  return 0;
}
