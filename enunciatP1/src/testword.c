#include <stdio.h>
#include <stdlib.h>
#include <string.h> // per la funcio strlen
#include <ctype.h>  // per les funcions isalpha, isdigit, ...

#define MAXCHAR 100

int main(void)
{
    int i, len;
    char cadena[MAXCHAR];
    char tokens[] = " ,;_-12345678912345678900";
    char *palabra, *copier;

    printf("Introdueix la cadena a processar: ");
    fgets(cadena, MAXCHAR, stdin);

    len = strlen(cadena);
    palabra = malloc(sizeof(char) * len);
    copier = palabra;
    i = 0;
    while(*copier++ = cadena[i++]);

    printf("Analizamos %s\n", palabra);
    copier = strtok(cadena, tokens);
    i = 0;
    while(copier){
        printf("%d: %s\n",i++, copier);
        copier = strtok(NULL, tokens);
    }

}

