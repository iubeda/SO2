#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv)
{
  FILE *fp;
  int i, size;
  double *a;

  size = 10;
  a = malloc(sizeof(double) * size);

  for(i = 0; i < size; i++)
    a[i] = sqrt((double) i);

  fp = fopen("vector.data", "w");

  if (!fp) {
    printf("ERROR: no he pogut obrir el fitxer.\n");
    exit(EXIT_FAILURE);
  }

  fprintf(fp, "%d\n", size);

  for (i = 0; i < size; i++)
    fprintf(fp, "%e\n", a[i]);

  fclose(fp);

  return 0;
}
