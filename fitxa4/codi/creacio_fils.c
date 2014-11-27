#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_t ntid;

void printids(const char *s)
{
  pid_t pid;
  pthread_t tid;

  pid = getpid();
  tid = pthread_self();
  printf("%s pid %u tid %u (0x%x)\n", s, (unsigned int)pid,
      (unsigned int)tid, (unsigned int)tid);
}

void *thr_fn(void *arg)
{
  printids("nou fil: ");
  return((void *)0);
}

int main(void)
{
  int err;

  err = pthread_create(&ntid, NULL, thr_fn, NULL);
  if (err != 0) {
    printf("no puc crear el fil.\n");
    exit(1);
  }
  printids("fil principal:");
  sleep(1);
  exit(0);
}
