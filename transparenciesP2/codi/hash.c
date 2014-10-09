#include <stdio.h>
#include <string.h> 

#define MAXCHAR 100
#define SIZE    100

int main(void)
{
  unsigned int i, len, seed, sum, hash;
  char cadena[MAXCHAR];

  printf("Introdueix la paraula: ");
  fgets(cadena, MAXCHAR, stdin);

  len = strlen(cadena) - 1; 
  sum = 0;
  seed = 131;
  for(i = 0; i < len; i++)
    sum = sum * seed + (int)cadena[i];

  hash = sum % SIZE;

  printf("El valor de hash es %d\n", hash);
}
