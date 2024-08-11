#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

typedef struct {
  char* key;
  char* value;
} ht_item;

typedef struct {
  int size;
  int base_size;
  int count;
  ht_item** items;
} ht_hash_table;

ht_hash_table* ht_new(void);
void ht_del_hash_table(ht_hash_table*);

void ht_insert(
    ht_hash_table*,
    const char*,
    const char*
);

char* ht_search(
    ht_hash_table*,
    const char*
);

void ht_delete(
    ht_hash_table*,
    const char*
);

#endif /* HASH_TABLE_H_ */
