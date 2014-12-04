#include "processer.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "file-parser.h"
#include "include/debug.h"
#include "indexer.h"

Processer_conf p_conf = { 0, 0, 0 };
pthread_mutex_t mutex_processer = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t pmutex_indexer = PTHREAD_MUTEX_INITIALIZER;


/**
 * Inits the processer scheme
 * Call this function before create threads madly
 * If this function is not called the shceme may not work
 * You are forewarned
 */
void init_processer(int last)
{
    p_conf.init = 1;
    p_conf.k = 0;
    p_conf.last = last;
}

/**
 * Returns the next element to be processed
 * Is a thread save function
 */
static int pnext()
{
    int num;

    pthread_t tid = pthread_self();
    
    //exclusio
    pthread_mutex_lock(&mutex_processer);
    if(DEBUGPTH)
        printf("Thread %i demana arxiu toca %i, l'ultim es %i\n",(int)tid, p_conf.k, p_conf.last);
    num = p_conf.k++;
    if(DEBUGPTH)
        printf("Thread %i rep arxiu %i, k queda %i\n",(int)tid, num, p_conf.k);
    pthread_mutex_unlock(&mutex_processer);
    //fi exclusio

    if(num >= p_conf.last)
    {
        if(DEBUGPTH)
            printf("Thread %i ja no procesara mes\n",(int)tid);
        num = -1;
    }
    return num;
}

/**
 *
 * @arg: estructura del tipo pthread_processer con la informacion necesaria (arxiu, tree)
 *
 *
 */
void *procesador(void *arg)
{
    if(!p_conf.init)
    {
        printf("Error: Processer scheme should be initialized before call procesador function\n");
        return NULL;
    }

    Hash_list *arxiu_procesat;
    Processer_context *context = (Processer_context *) arg;

    Str_array *arxius = context->llista;
    RBTree *tree = context->tree;
    pthread_t tid = pthread_self();
    int narxiu;
    FILE *fl;

    // will not enter when pnext returns -1
    // it means that the list is ended
    // comparation is required because the first element
    // is in tthe position 0
    while( (narxiu = pnext()) != -1 )
    {
        if(DEBUGPTH)
            printf("Thread %i processant arxiu %i\n",(int)tid, narxiu);

        fl = fopen(arxius->data[narxiu], "r");

        arxiu_procesat = fparser(fl);

        fclose(fl);

        //TODO call indexar_llista_golbal
        pthread_mutex_lock(&pmutex_indexer);
            if(DEBUGPTH)
                printf("Thread %i demana indexar \n",(int)tid);
            // un cop tenim l'arxiu procesat en una hash_list, l'indexem
        indexar_en_llista_global(tree, arxiu_procesat, arxius->length,  narxiu);
            if(DEBUGPTH)
                printf("Thread %i termina d'indexar\n",(int)tid);
        pthread_mutex_unlock(&pmutex_indexer);

        free_hash_list(arxiu_procesat);
        free(arxiu_procesat);
    }

    return NULL;
}
