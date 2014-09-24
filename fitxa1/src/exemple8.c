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
  struct camp *a, *pos, *end;

  a = malloc(sizeof(struct camp) * 5);

  if (!a)
  {
    printf("No he pogut reservar la memòria\n");
    exit(1);
  }

  end = a + 5;

  for(pos = a; pos < end; pos++)
  {
    pos->identificador = 0;
    pos->valor = 0.0;
  }

  free(a);

  return 0;
}
