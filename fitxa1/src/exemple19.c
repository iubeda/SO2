#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

#define MAXLEN 100

int main(void) 
{
  int i;
  char str[MAXLEN];
  char *cad; 

  if (fgets(str, MAXLEN, stdin) == NULL) { 		
    printf("No s'ha entrat cap cadena.\n"); 	
  }

  i = 1;
  cad = strtok(str, ";");	
  while (cad) {
    printf("Cadena %d: %s\n", i, cad);
    i++;
    cad = strtok(NULL, ";");
  }

  return 0; 
}
