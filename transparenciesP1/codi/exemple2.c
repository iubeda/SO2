#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int a[10];
  
  printf("Abans assignacio\n");
  a[15] = 15;
  printf("Despres assignacio\n");
  
  printf("Valor a[15]: %d\n", a[15]);
}