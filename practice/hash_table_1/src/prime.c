#include <math.h>
#include "prime.h"

/* 1 - prime, 0 - not prime, -1 - undefined */
int is_prime(const int x)
{
  if (x < 2) return -1;
  if (x < 4) return 1;
  if (x % 2 == 0) return 0;
  double upper_bound = floor(sqrt((double) x));
  for (int i = 3; i <= upper_bound; i += 2)
    if (x % i == 0) return 0;
  return 1;
}

int next_prime(int x)
{
  while (is_prime(x) != 1) ++x;
  return x;
}
