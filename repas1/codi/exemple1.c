#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int global;

int main(void)
{
  int mida;
  char str[10];

  int local, *vector;

  global = 0;
  local  = 0;

  printf("PID del procés %d\n", getpid());
  printf("Funcio main: %lx\n", (unsigned long) &main);
  printf("Variable global: %lx\n", (unsigned long) &global);
  printf("Variable local: %lx\n", (unsigned long) &local);
  printf("Variable vector: %lx\n", (unsigned long) &vector);

  printf("Polsa enter per continuar.\n");
  fgets(str, 10, stdin);
  printf("Introdueix mida de bytes a reservar:\n");
  fgets(str, 10, stdin);

  mida = atoi(str);
  vector = malloc(mida);
  printf("Vector apunta a: %lx\n", (unsigned long) vector);

  printf("Polsa enter per continuar.\n");
  fgets(str, 10, stdin);

  free(vector);

  printf("Memòria alliberada.\n");
  printf("Polsa enter per continuar.\n");
  fgets(str, 10, stdin);

  return 0;
}
