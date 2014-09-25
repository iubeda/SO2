#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int *a, i;
  
  a = (int *) malloc(sizeof(int) * 10);
  
  for(i = 0; i < 10; i++)
    a[i] = 0;
  
  // No alliberem la memoria
}