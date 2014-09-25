#include <stdio.h>
#include <stdlib.h>

// This function is in example.c
int dummy_function(char *str);

/**
 *
 * Main function. This is just a small dummy example used to see if the
 * Makefile works properly.
 *
 */
 
int main(int argc, char **argv)
{
  if (argc != 2) {
    printf("Us: %s fitxer.cfg\n", argv[0]);
    exit(1);
  }

  dummy_function(argv[1]);

  return 0;
}
