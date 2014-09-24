#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 100

int main(void)
{
  int i, j, k, npunticoma, nsubcadenes;
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

  // Ara reservem memoria per nsubcadenes cadenes de 
  // caràcters de longitud MAXLEN

  subcadena = malloc(sizeof(char *) * nsubcadenes);
  for(i = 0; i < nsubcadenes; i++)
    subcadena[i] = malloc(sizeof(char) * MAXLEN);

  // I ara tornem a passar per la cadena original per
  // generar les subcadenes

  j = 0;
  i = 0;
  while (j < nsubcadenes) {
    k = 0;
    while ((str[i] != '\0') && (str[i] != ';')) {
      subcadena[j][k] = str[i];
      i++;
      k++;
    }
    subcadena[j][k] = '\0';
    j++;
    i++;
  }

  // Les imprimimim

  printf("Les subcadenes trobades són:\n");

  for(i = 0; i < nsubcadenes; i++)
    printf("Sucadena %d: %s\n", i+1, subcadena[i]);

  // Alliberem memoria

  for(i = 0; i < nsubcadenes; i++)
    free(subcadena[i]);

  free(subcadena);

  return 0;
}

