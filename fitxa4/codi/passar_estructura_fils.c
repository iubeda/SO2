#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_t ntid[10];

struct parametres {
  int i;
  int j;
  char *str;
};

void *thr_fn(void *arg)
{
  struct parametres *par = (struct parametres *) arg;
  printf("El fil amb sencer %d te assignat la j = %d i str = %s\n", par->i, par->j, par->str);
  return NULL;
}

int main(void)
{
  int i, err;
  void *tret;
  struct parametres *par;

  for(i = 0; i < 10; i++) {
    par = malloc(sizeof(struct parametres));
    par->i = i; 
    par->j = 10 - i;
    par->str = malloc(sizeof(char) * 10);
    sprintf(par->str, "Hola %d", i);
    err = pthread_create(ntid+i, NULL, thr_fn, (void *) par);
  }

  for(i = 0; i < 10; i++) {
    err = pthread_join(ntid[i], &tret);
  }

  return 0;
}
