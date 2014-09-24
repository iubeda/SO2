#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 100

int main(void)
{
  int i, j, npunticoma, nsubcadenes;
  char **subcadena;
  char str[MAXLEN];

  if (fgets(str, MAXLEN, stdin) == NULL) {
    printf("No s'ha entrat cap cadena.\n");
  }

  // Comencem comptant el nombre de ";" que apareixen

  npunticoma = 0;
  while (str[i] != '\0') {
    if (str[i] == ';')
      npunticoma++;
    i++;
  }

  // El nombre de subcadenes és ...

  nsubcadenes = npunticoma + 1;

  // Ara reservem memoria per nsubcadenes punters a
  // cadenes de caràcters

  subcadena = malloc(sizeof(char *) * nsubcadenes);

  // I ara tornem a passar per la cadena original per
  // generar les subcadenes

  j = 0;
  i = 0;
  while (j < nsubcadenes) {
    subcadena[j] = str + i;
    while ((str[i] != '\0') && (str[i] != ';'))
      i++;
    str[i] = '\0';
    i++;
    j++;
  }

  // Les imprimimim

  printf("Les subcadenes trobades són:\n");

  for(i = 0; i < nsubcadenes; i++)
    printf("Sucadena %d: %s\n", i+1, subcadena[i]);

  // Alliberem memoria

  free(subcadena);

  return 0;
}

