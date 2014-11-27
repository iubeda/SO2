#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct foo {
  int a, b, c, d;
};

void printfoo(const char *s, const struct foo *fp)
{
  printf(s);
  printf("  estructura ubicada a la direccio 0x%x\n", (unsigned)fp);
  printf("  foo.a = %d\n", fp->a);
  printf("  foo.b = %d\n", fp->b);
  printf("  foo.c = %d\n", fp->c);
  printf("  foo.d = %d\n", fp->d);
}

void *thr_fn1(void *arg)
{
  struct foo foo = {1, 2, 3, 4};

  printfoo("fil 1:\n", &foo);
  return ((void *)&foo);
}

void *thr_fn2(void *arg)
{
  printf("fil 2 amb identificador %d\n", pthread_self());
  return ((void *)0);
}

int main(void)
{
  int err;
  pthread_t tid1, tid2;
  struct foo *fp;

  err = pthread_create(&tid1, NULL, thr_fn1, NULL);
  err = pthread_join(tid1, (void *)&fp);

  sleep(1);
  
  printf("El fil principal crea un segon fil.\n");
  err = pthread_create(&tid2, NULL, thr_fn2, NULL);
  sleep(1);
  printfoo("fil principal:\n", fp);
  return 0;
}
