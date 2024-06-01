#include <stdio.h>
#include "../include/tim_list.h"

static int square_(int x) { return x * x; }

int main(void) {
	List list;
	init_list(&list);

	free_list(&list);
	return 0;
}
