#include "indexer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "include/const.h"
#include "file-list.h"
#include "hash-list.h"
#include "red-black-tree.h"


/**
 *
 * Funcio que inicialitza el buffer, es propietat de l'indexador
 * 
 */
int init_indexer(int size)
{
    //inicializamos el ibuffer
    ibuffer->length = size;
    ibuffer->pposition = 0;
    ibuffer->iposition = 0;
    ibuffer->end = 0;
    // allocatamos todo a null
    ibuffer->buffer = calloc(size, sizeof(Hash_list*));

    return 0; 
}
/*
 * Funcio que allibera els recursos del indexer
 */
int end_indexer()
{
    free(ibuffer->buffer);
    return 0;
}

/**
 * Funcio que rep un tree i un arxiu procesar en format hash list
 * i l'indexa
 * @ tree : arbre on s'indexar
 * @ aproc : arxiu procesat a indexar
 * @ num_arxius : numero dp'arxius total
 * @ arxiu : numero d'arxiu a procesar
 * */
void indexar_en_llista_global(RBTree *tree, Hash_list *aproc, int num_arxius,  int arxiu)
{
    int i, len;
    RBData *treeData;
    ListItem *currentItem;
    ListData *data;


    // recorremos cada posicion de la lista hash
    for(i = 0; i < aproc->length; i++)
    {
        if(DEBUG){
            printf("Dumping list %i, file %i\n", i, arxiu);
            dumpList(aproc->data[i]);
            printf("*\t*\t*\n");
        }
        //indexamos el contenido de esta lista enlazada
        //indexar_llista_enllasada(tree, aproc->data[i], aproc->length);

        //recuperem el primer node de la llista
        currentItem = aproc->data[i]->first;
        while(currentItem != NULL)
        {
            data = currentItem->data;
            //busquem la paraula a l'arbre
//                pthread_mutex_lock(&mutex_indexer);
            treeData = findNode(tree, data->primary_key);
//                pthread_mutex_unlock(&mutex_indexer);
            if(treeData != NULL) // si la paraula esta a l'arbre
            {
                // augmentem en 1 el numero d'arxius en el que surt la paraula
                // i marquem el numero de cops que surt a l'arxiu
                treeData->numFiles++;
                treeData->numTimes[arxiu] = data->numTimes;

            }
            else
            {
                // si no esta, hem d'allocatar, inicialitzar el data
                // copiar la paraula, copiar el numero de cops per arxiu
                // i aumengtar el numer d'arxus
                treeData = malloc(sizeof(RBData));

                len = strlen(data->primary_key);
                initRBData(treeData, len,num_arxius);
                strcpy(treeData->primary_key, data->primary_key);
                treeData->numTimes[arxiu] = data->numTimes;
                treeData->numFiles++;
//                    pthread_mutex_lock(&mutex_indexer);
                insertNode(tree, treeData);
//                    pthread_mutex_unlock(&mutex_indexer);


                // si esta palabra es mas larga que la almacenada como larga,
                // la guardamos
                /* selects which the longest word is */
                len = strlen(data->primary_key);

//                    pthread_mutex_lock(&mutex_indexer);
                if(tree->properties->longest->length < len)
                {
                    //this data contains the new longest word
                    tree->properties->longest->length = len;
                    tree->properties->longest->file = arxiu;
                    tree->properties->longest->word = treeData->primary_key;
                }
//                    pthread_mutex_unlock(&mutex_indexer);

            }
            currentItem = currentItem->next;

        }
    }
} 
