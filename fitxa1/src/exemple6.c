#include <stdio.h>
#include <stdlib.h>

struct camp
{
  int identificador;
  double valor;
};

int main(void)
{
  int i;
  struct camp *a;

  a = malloc(sizeof(struct camp) * 5);

  if (!a)
  {
    printf("No he pogut reservar la memòria\n");
    exit(1);
  }

  for(i = 0; i < 5; i++)
  {
    a[i].identificador = 0;
    a[i].valor = 0.0;
  }

  free(a);

  return 0;
}
