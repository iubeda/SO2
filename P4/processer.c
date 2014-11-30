#include "processer.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "file-parser.h"

Processer_conf p_conf = { 0, 0, 0 };
pthread_mutex_t mutex_processer = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_indexer = PTHREAD_MUTEX_INITIALIZER;


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

    //exclusio
    pthread_mutex_lock(&mutex_processer);
    num = p_conf.k++;
    pthread_mutex_unlock(&mutex_processer);
    //fi exclusio
    
    if(num > p_conf.last)
        num = -1;

    return num;
}

void *procesador(void *arg)
{
    Hash_list *arxiu_procesat;
    Processer_context *context = (Processer_context *) arg;

    Str_array *arxius = context->llista;
    RBTree *tree = context->tree;

    int narxiu;
    FILE *fl;

    // will not enter when pnext returns -1
    // it means that the list is ended
    // comparation is required because the first element
    // is in tthe position 0
    while( (narxiu = pnext()) != -1 )
    {
        fl = fopen(arxius->data[narxiu], "r");
        arxiu_procesat = fparser(fl);

        //TODO call indexar_llista_golbal

        fclose(fl);
        free_hash_list(arxiu_procesat);
        free(arxiu_procesat);
    }
    
    return NULL;
}
