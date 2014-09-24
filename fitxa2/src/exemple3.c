#include <stdio.h> 
#include <stdlib.h>

int main(int argc, char **argv)
{
  FILE *fp;
  int i, size, nelems;
  double *a;

  fp = fopen("vector.data", "r");

  if (!fp) {
    printf("ERROR: no he pogut obrir el fitxer.\n");
    exit(EXIT_FAILURE);
  }

  nelems = fread(&size, sizeof(int), 1, fp);

  if (nelems != 1) {
    printf("ERROR: el fitxer és massa curt.\n");
    exit(EXIT_FAILURE);
  }

  if (size <= 0) {
    printf("ERROR: la mida no és correcta.\n");
    exit(EXIT_FAILURE);
  }

  a = malloc(sizeof(double) * size);

  nelems = fread(a, sizeof(double), size, fp);

  if (nelems != size) {
    printf("ERROR: el fitxer és massa curt.\n");
    exit(EXIT_FAILURE);
  }

  fclose(fp);

  printf("Hi ha %d valors guardats al fitxer.\n", nelems);
  printf("Els valors son: ");

  for(i = 0; i < 10; i++)
    printf(" %f, ", a[i]);

  printf("\n");

  free(a);

  return 0;
}
