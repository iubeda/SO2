#include <stdio.h>
#include <stdlib.h>
#include "include/const.h"
#include "file-list.h"
#include "file-parser.h"
#include "linked-list.h"
#include "hash-list.h"

/**
 * indexa un arxiu en estructura global
 */
int indexar_llistat(List *hash_list)
{
    //TODO
    /*
    ListItem *current;

    current = hash_list->first;

    while (current != NULL)
    {
        if (findNode(  ARBOL , current->data->primary_key)){
        
            
        }else{
        
            
        }

        current = current->next;
    }
    */
}

/**
 * procesa un llistat d arxius
 */
int processar_llista_arxius(Str_array *arxius)
{
    int i,j;
    Hash_list *arxiu_procesat;

    // recorrem el llistat d'arxius
    for( i = 0; i < arxius->length; i++ )
    {
        FILE *fl;
        fl = fopen(arxius->data[i], "r");
        // si no podem obrir l'arxiu, pasem al seguent
        if(!fl) continue;

        arxiu_procesat = fparser(fl);

        // todo va bien, no devuelve NULL,  vamos a indexar
        for( j = 0; j < arxiu_procesat->length; j++ )
        {
            // Debug hash list
                printf("\n ---> Hash list index %i \n\n", j);
                dumpList(arxiu_procesat->data[j]);
            //indexar_llistat( arxiu_procesat->data[j] );
            //printf("tengo %i \n", arxiu_procesat->data[j]->numItems);
        }
        
        fclose(fl);
        
        // alliberem memoria
        free_hash_list(arxiu_procesat);
        free(arxiu_procesat);

    }

}

/**
 *
 * Main function
 *
 */
int main(int argc, char **argv)
{
    Str_array *paraules;
    /* comprobem si hi ha parametre d'entrada */
    if (argc != 2)
    {
        printf("Exemple d'us: %s fitxer.cfg\n", argv[0]);
        exit(1);
    }

    /* cridem a la funcio del llistat de paraules que retorna un struct */
    paraules = flist(argv[1]);
    processar_llista_arxius(paraules);


    // liberamos memoria
    int iter;
    for(iter = 0; iter < paraules->length; iter++)
    {
        free(paraules->data[iter]);
    }
    free(paraules->data);
    free(paraules);
    return 0;
}
