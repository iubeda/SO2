#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int i, j, *a;

  for(i = 0; i < 1000; i++)
  {
    a = malloc(sizeof(int) * 5);

    if (a == NULL)
    {
      printf("No he pogut reservar la memòria\n");
      exit(1);
    }

    for(j = 0; j < 5; j++)
      a[j] = 0;
  }

  free(a);

  return 0;
}
