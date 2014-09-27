#include <stdio.h>
#include <stdlib.h>

// Funcio inclosa al arxiu parser.c
int aarxiu(char *str);

/**
 *
 * Main function. This is just a small dummy example used to see if the
 * Makefile works properly.
 *
 */
 
int main(int argc, char **argv){
    // comprobem si hi ha parametre d'entrada
    if (argc != 2){
        printf("Exemple d'us: %s fitxer.cfg\n", argv[0]);
        exit(1);
    }

    // cridem a la funcio del parser
    aarxiu(argv[1]);

    return 0;
}
