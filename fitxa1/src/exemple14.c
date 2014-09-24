#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
  int i;
  char *a;

  a = malloc(sizeof(char) * 100);

  strcpy(a, "Bon dia!\n");	
  printf("%s",a);

  return 0;
}
