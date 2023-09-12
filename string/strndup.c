#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *xstrndup(const char *s, size_t n)
{
  size_t len = 0;

  while (len < n && s[len]) {
    len++;
  }

  char *c = malloc(len + 1);
  if (c) {
    memcpy(c, s, len);
    c[len] = 0;
  }

  return c;
}

int main()
{
  char *s = xstrndup("hello!", 4);

  printf("%s\n", s);

  free(s);
  return 0;
}
