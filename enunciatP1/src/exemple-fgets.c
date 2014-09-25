#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  char str[100];
  FILE *fp;

  fp = fopen("fitxer.txt", "r");
  if (!fp) {
    printf("No he pogut obrir fitxer.\n");
    exit(1);
  }

  fgets(str, 100, fp);
  while (!feof(fp)) {
     printf("Linia: %s\n", str);
     fgets(str, 100, fp);
  }

  fclose(fp);
}
