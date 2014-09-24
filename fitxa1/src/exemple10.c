#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int i;
  int *a;

  a = malloc(sizeof(int) * 5);

  if (a == NULL)
  {
    printf("No he pogut reservar la memòria\n");
    exit(1);
  }

  printf("Començo a escriure zeros...\n");

  for(i = 1000; i < 1100; i++)
    a[i] = 0;

  printf("He escrit els zeros!\n");

  free(a);

  return 0;
}
