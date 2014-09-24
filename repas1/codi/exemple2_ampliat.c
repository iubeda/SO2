#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char str[10];

int main(void)
{
   printf("PID del procés %d\n", getpid());
   funcio_recursiva(0);
}

int funcio_recursiva(int n)
{
  int a[1000];
  
  printf("%d\n", n);

  if (n == 0)
    fgets(str, 10, stdin);

  if (n == 2075)
    fgets(str, 10, stdin);
  
  funcio_recursiva(n+1);
}
   
