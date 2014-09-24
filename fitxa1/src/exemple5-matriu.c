#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int i, j, **a;

  a = malloc(sizeof(int *) * 1000);
  
  for(i = 0; i < 1000; i++)
  {
    a[i] = malloc(sizeof(int) * 5);

    if (a[i] == NULL)
    {
      printf("No he pogut reservar la memòria\n");
      exit(1);
    }

    for(j = 0; j < 5; j++)
      a[i][j] = 0;
  }
  
  /* Processem les dades .... */
  
  
  /* I alliberem en acabar de processar */

  for(i = 0; i < 1000; i++)
      free(a[i]);
  
  free(a);

  return 0;
}
