#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int c;
  FILE *fp;

  fp = fopen("fitxer.txt", "r");
  if (!fp) {
    printf("No he pogut obrir fitxer.\n");
    exit(1);
  }

  c = fgetc(fp);
  while (!feof(fp)) {
     printf("Caracter: %c (byte %d)\n", c, c);
     c = fgetc(fp);
  }

  fclose(fp);
}
