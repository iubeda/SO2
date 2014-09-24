#include <stdio.h>
#include <stdlib.h>

int main(void)
{
   funcio_recursiva(0);
}

int funcio_recursiva(int n)
{
  int a[1000];
  
  printf("%d\n", n);
  
  funcio_recursiva(n+1);
}
   
