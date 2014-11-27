#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_t ntid[10];

void *thr_fn(void *arg)
{
  int i = (int) arg;
  printf("El fil amb ID %d te assignat el sencer %d\n", pthread_self(), i);
  return((void *)i);
}

int main(void)
{
  int i, err;
  void *tret;

  for(i = 0; i < 10; i++) {
    err = pthread_create(ntid+i, NULL, thr_fn, (void *) i);
    if (err != 0) {
      printf("no puc crear el fil.\n");
      exit(1);
    }
  }

  for(i = 0; i < 10; i++) {
    err = pthread_join(ntid[i], &tret);
    if (err != 0) {
      printf("error pthread_join amb fil %d\n", i);
      exit(1);
    }
    printf("El fil %d m'ha retornat el numero %d\n", i, (int) tret);
  }

  return 0;
}
