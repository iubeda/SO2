#include <stdio.h>

#define MAXLINE 100

int main(void) 
{ 	
  char buf[MAXLINE];
  while (fgets(buf, MAXLINE, stdin) != NULL) 		
    fputs(buf, stdout);

  return 0; 
} 
