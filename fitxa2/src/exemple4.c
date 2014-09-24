#include <stdio.h>

#define MAXLINE 100

int main(void) 
{ 	
  char buf[MAXLINE];
  while (fscanf(stdin, "%s", buf) != EOF) 		
    fprintf(stdout, "%s\n", buf);

  return 0; 
} 
