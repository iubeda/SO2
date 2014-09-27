#include <stdio.h>
#include <string.h>

/**
 *
 * The dummy function. Note that this function is called from another file.
 *
 */

int dummy_function(char *cadena)
{
  int len;


  len = strlen(cadena);

  printf("The argument to dummy function is: %s\n", cadena);
  printf"The length of the string is: %d\n", len);

  return 0;
}
