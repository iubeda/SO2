#include <stdio.h>
#include <stdlib.h>
#include "include/const.h"
#include "file-list.h"
#include "file-parser.h"
#include "linked-list.h"

/**
 *
 * Main function
 *
 */
 

/**
 * indexa un arxiu en estructura global
 */
int indexar_llistat(List hash_list[])
{
    //TODO
}

/**
 * procesa una arxiu
 */
int processar_arxiu(char *nom_arxiu)
{
    //TODO
}

/**
 * procesa un llistat de paraules
 */
int processar_arxius(STR_ARRAY paraules)
{
    //TODO

}
int main(int argc, char **argv)
{
    STR_ARRAY paraules;
    /* comprobem si hi ha parametre d'entrada */
    if (argc != 2)
    {
        printf("Exemple d'us: %s fitxer.cfg\n", argv[0]);
        exit(1);
    }

    /* cridem a la funcio del llistat de paraules que retorna un struct */
    paraules = flist(argv[1]);
    int iter;
    for(iter = 0; iter < paraules.length; iter++)
    {
        printf("%s\n", paraules.data[iter]);
        free(paraules.data[iter]);
    }
    free(paraules.data);
    return 0;
}
