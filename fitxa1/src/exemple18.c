#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 100

int main(void)
{
  int nargs;
  char str[MAXLEN];
  char cad1[MAXLEN], cad2[MAXLEN], cad3[MAXLEN];

  if (fgets(str, MAXLEN, stdin) == NULL) {
    printf("No s'ha entrat cap cadena.\n");
  }

  nargs = sscanf(str, "%[^;];%[^;];%[^\n]", 
      cad1, cad2, cad3);

  printf("%d\n", nargs);

  if (nargs != 3) {
    printf("Format incorrecte.\n");
    exit(1);
  }

  printf("Cadena 1: %s\n", cad1);
  printf("Cadena 2: %s\n", cad2);
  printf("Cadena 3: %s\n", cad3);

  return 0;
}

