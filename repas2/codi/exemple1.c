#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int global;
int global2 = 2;

int main(void)
{
  char str[10], *str2;
  int local, mida, *vector;

  str2 = "Hola";
  global = 0;
  local  = 0;

  printf("PID del procés %d\n", getpid());
  printf("La funcio main es a direccio 0x%lx\n", (long) &main);
  printf("Variable global es a direcció 0x%lx\n", (long) &global);
  printf("Variable global2 es a direcció 0x%lx\n", (long) &global2);
  printf("Variable str apunta es a 0x%lx\n", str);
  printf("Variable str2 apunta es a 0x%lx\n", str2);
  printf("Variable local es a direcció 0x%lx\n", (long) &local);

  printf("Polsa enter per continuar.\n");
  fgets(str, 10, stdin);
  printf("Introdueix mida de bytes a reservar:\n");
  fgets(str, 10, stdin);

  mida = atoi(str);
  vector = malloc(mida);
  printf("Memòria dinàmica a direcció 0x%lx\n", (long) vector);

  printf("Polsa enter per continuar.\n");
  fgets(str, 10, stdin);

  free(vector);

  printf("Memòria alliberada.\n");
  printf("Polsa enter per continuar.\n");
  fgets(str, 10, stdin);

  return 0;
}
