#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
     str[strlen(str) - 1] = '\0';
     printf("Linia len(%lu) : %s\n",strlen(str), str);
     fgets(str, 100, fp);
  }
     printf("Linia: %s\n", str);


  fclose(fp);
}
