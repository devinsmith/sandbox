#include <alloca.h>
#include <pthread.h>
#include <stdio.h>
void* threadfunc (void*p) {
  int n = 0;
  for (;;) {
    printf("Allocated %d bytes\n", n);
    fflush(stdout);
    n += 128;
    *((volatile char *) alloca(128)) = 0;
  }
}

int main()
{
  pthread_t thread;
  pthread_create(&thread, NULL, threadfunc, NULL);
  for (;;) {}
}

