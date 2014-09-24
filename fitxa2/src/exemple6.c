#include <stdio.h> 
#include <stdlib.h>

int main(int argc, char **argv)
{
  FILE *fp;
  int i, nelems, size;
  double *a;

  fp = fopen("vector.data", "r");

  if (!fp) {
    printf("ERROR: no he pogut obrir el fitxer.\n");
    exit(EXIT_FAILURE);
  }

  nelems = fscanf(fp, "%d", &size);

  if (nelems != 1) {
    printf("ERROR: el fitxer és massa curt.\n");
    exit(EXIT_FAILURE);
  }

  a = malloc(sizeof(double) * size);

  printf("Hi ha %d valors guardats al fitxer.\n", size); 
  printf("Els valors son: ");

  for (i = 0; i < 10; i++)
  {
    nelems = fscanf(fp, "%le", a+i); // &(a[i]) 

    if (nelems != 1) {
      printf("ERROR: el fitxer és massa curt.\n");
      exit(EXIT_FAILURE);
    }

    printf("%f, ", a[i]);
  }

  printf("\n");

  fclose(fp);
  free(a);

  return 0;
}
