#include "../include/predicate_module.h"

static const predmodule null_predmod = {
  .state = UNDEFINED,
  .pred = NULL,
  .accumulator = NULL,
  .sd = {
    .storage_begin = NULL,
    .storage_current = NULL,
    .storage_end = NULL
  },
  .cd = {
    .equals = true
  },
  .ad = NULL
};

void init_predmod(predmodule* predmod, predstate state) {
  *predmod = null_predmod;
  predmod->state = state;
}

void set_predicate(predmodule* predmod, void* pred) {
  predmod->pred = pred;
}

void set_accumulator(predmodule* predmod, void* accumulator) {
  predmod->accumulator = accumulator;
}

void set_storage(predmodule* predmod, void* begin, void* end) {
  predmod->sd.storage_begin = begin;
  predmod->sd.storage_current = begin;
  predmod->sd.storage_end = end;
}

void free_avl_data(predmodule* predmod) {
  predmod->ad = (avl_data*) malloc(sizeof(avl_data));
  predmod->ad->valid = true;
  predmod->ad->nodes = 0;
  predmod->ad->elems = 0;
}

void clear_predmod(predmodule* predmod) {
  if (predmod->ad == NULL) return;
  free(predmod->ad);
  predmod->ad = NULL;
}
