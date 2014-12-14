#include "indexer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "include/const.h"
#include "include/debug.h"
#include "file-list.h"
#include "hash-list.h"
#include "red-black-tree.h"

static void indexar_en_llista_global(RBTree *tree, Hash_list *aproc);
/**
 *
 * Funcio que inicialitza el buffer, es propietat de l'indexador
 *
 */
int init_indexer(int buffer_size)
{
    //inicializamos el ibuffer
    ibuffer = malloc(sizeof(Indexer_buffer));
    ibuffer->length = buffer_size;
    ibuffer->pposition = 0;
    ibuffer->iposition = 0;
    ibuffer->end = 0;
    ibuffer->quantity = 0;
    // allocatamos todo a null
    ibuffer->buffer = calloc(buffer_size, sizeof(Hash_list*));
    //ibuffer->buffer = malloc(sizeof(Hash_list*)* buffer_size);
    return 0;
}
/*
 * Funcio que allibera els recursos del indexer
 */
int end_indexer()
{
    free(ibuffer->buffer);
    free(ibuffer);
    return 0;
}

/**
 * Funcion que controla el siguiente elemento del buffer a indexar
 */
static Hash_list *inext()
{
    Hash_list *next_element;
    pthread_mutex_lock(&mutex_shared);
    if(DEBUGPTH)
        printf("Indexer accedeix per a recuperar el element buffer\n");

    next_element = NULL;
    
    // mentre next_element sigui null
    while( !next_element )
    {
        // si es la fi
        if( ibuffer->end )
        {
            if(DEBUGPTH)
                printf("Indexer termina de treballar y surt\n");

            break;
        }
        else if( !ibuffer->quantity )
        {
            pthread_cond_wait(&cond_indexar, &mutex_shared);
            if(DEBUGPTH)
                printf("Indexer desperta\n");
            continue;
        }

        if(DEBUGPTH)
            printf("El buffer conte elements, indexer continua\n");

        next_element = ibuffer->buffer[ibuffer->iposition++];
        ibuffer->iposition %= ibuffer->length;
        ibuffer->quantity--;

        // usamos el signal para despertar solo a un hilo
        pthread_cond_signal( &cond_procesar );

    }

    pthread_mutex_unlock( &mutex_shared );

    return next_element;

}


void *indexador(void *arg)
{
    // recuperamos los argumentos
    Indexer_context *icontext = (Indexer_context *) arg;
    RBTree *tree = icontext->tree;
    Hash_list *llista;
    // cada vez que la funcion inext devuelva algo valido
    while( (llista = inext()) )
            indexar_en_llista_global(tree, llista);

    // liberamos recursos
    end_indexer();

    return NULL;

}

/**
 * Funcio que rep un tree i un arxiu procesar en format hash list
 * i l'indexa
 * @ tree : arbre on s'indexar
 * @ aproc : arxiu procesat a indexar
 * */
static void indexar_en_llista_global(RBTree *tree, Hash_list *aproc)
{
    int i, len, num_arxius, arxiu;
    RBData *treeData;
    ListItem *currentItem;
    ListData *data;
    num_arxius = aproc->totalarxius;
    arxiu = aproc->number;


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
            treeData = findNode(tree, data->primary_key);

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

                insertNode(tree, treeData);

                // si esta palabra es mas larga que la almacenada como larga,
                // la guardamos
                /* selects which the longest word is */
                len = strlen(data->primary_key);

                if(tree->properties->longest->length < len)
                {
                    //this data contains the new longest word
                    tree->properties->longest->length = len;
                    tree->properties->longest->file = arxiu;
                    tree->properties->longest->word = treeData->primary_key;
                }

            }
            currentItem = currentItem->next;

        }
    }

    free_hash_list(aproc);
    free(aproc);
}
