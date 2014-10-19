#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/const.h"
#include "file-list.h"
#include "file-parser.h"
#include "linked-list.h"
#include "hash-list.h"
#include "red-black-tree.h"

/**
 * indexa un arxiu en estructura global
 */
void indexar_llistat(List *hash_list, RBTree *tree)
{
    //TODO
    int pos, len;
    RBData *treeData;
    ListItem *current;

    current = hash_list->first;

    while (current != NULL)
    {
        if ( (treeData = findNode(  tree, current->data->primary_key)) ){
            
            pos = treeData->num++;
            treeData->string[pos] = current->data->numTimes;
            
        }else{
            // If the key is not in the tree, allocate memory for the data
            // and insert in the tree
            
            len = strlen(current->data->primary_key);
            
            treeData = malloc(sizeof(RBData));
            // allocatamos el espacio necesario
            treeData->primary_key = malloc( (sizeof(char) * len)+1 );
            // copiamos la pk a treeData
            strcpy(treeData->primary_key, current->data->primary_key);
            treeData->string = malloc(sizeof(char) * 10);
            treeData->string[0] = current->data->numTimes;
            treeData->num = 1;

            insertNode( tree, treeData );
        }

        current = current->next;
    }
    
}

/**
 * procesa un llistat d arxius
 */
int processar_llista_arxius(Str_array *arxius, RBTree *tree)
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
                //printf("\n ---> Hash list index %i \n\n", j);
                //dumpList(arxiu_procesat->data[j]);
            indexar_llistat( arxiu_procesat->data[j] , tree);
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
    RBTree tree;
    RBData *data;
    
    /* comprobem si hi ha parametre d'entrada */
    if (argc != 2)
    {
        printf("Exemple d'us: %s fitxer.cfg\n", argv[0]);
        exit(1);
    }
    
    // iniciamos el arbol
    initTree(&tree);
    
    /* cridem a la funcio del llistat de paraules que retorna un struct */
    paraules = flist(argv[1]);
    processar_llista_arxius(paraules, &tree);


    // liberamos memoria
    int iter;
    for(iter = 0; iter < paraules->length; iter++)
    {
        free(paraules->data[iter]);
    }
    free(paraules->data);
    free(paraules);
    
    /*P2: testeo cutre del arbol*/
    data = tree.root->data;  
    printf("palabra: %s | puntero %p | numfiles: %i | info: %i\n", data->primary_key, data->primary_key, 
           data->num, data->string[0]);
  
    /* Delete the tree */
    deleteTree( &tree );
    
    return 0;
}
