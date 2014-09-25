#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  char str[20];
  FILE *fp;

  fp = fopen("fitxer.txt", "r");
  if (!fp) {
    printf("No he pogut obrir fitxer.\n");
    exit(1);
  }

  fscanf(fp, "%s", str);
  while (!feof(fp)) {
     printf("Dades llegides: %s\n", str);
     fscanf(fp, "%s", str);
  }

  fclose(fp);
}
