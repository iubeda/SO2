#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int i;
  int *a, *b;

  a = malloc(sizeof(int) * 5);

  if (a == NULL)
  {
    printf("No he pogut reservar la memòria\n");
    exit(1);
  }

  b = a + 1;

  for(i = -1; i < 4; i++)
    b[i] = 0;

  free(a);

  return 0;
}
