#ifndef XMALLOC_H_
#define XMALLOC_H_

void *xmalloc(size_t size);
void *xcalloc(size_t nmemb, size_t size);
void *xrealloc(void *ptr, size_t size);
char *xstrdup(const char *s);

#endif /* SMALLOC_H_ */
