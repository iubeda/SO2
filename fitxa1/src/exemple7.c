#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int *a, *pos, *end;

  a = malloc(sizeof(int) * 5);

  if (a == NULL)
  {
    printf("No he pogut reservar la memòria\n");
    exit(1);
  }

  end = a + 5;

  for(pos = a; pos < end; pos++)
    *pos = 0;

  free(a);

  return 0;
}
