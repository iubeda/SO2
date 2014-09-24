#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 10

void main(int argc, char **argv)
{
	char str[MAXLEN];

	if (argc != 2) {
		printf("Usage: %s cadena\n", argv[0]);
		exit(1);
	}

	// Copiem argv[1] a str
	strcpy(str, argv[1]);

	printf("%s\n", str);
}
