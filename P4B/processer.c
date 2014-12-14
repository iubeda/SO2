#include "processer.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "file-parser.h"
#include "include/debug.h"
#include "indexer.h"

Processer_conf p_conf = { 0, 0, 0 };
pthread_mutex_t mutex_processer = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_shared = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond_indexar = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_procesar = PTHREAD_COND_INITIALIZER;

/**
 * Inits the processer scheme
 * Call this function before create threads madly
 * If this function is not called the scheme may not work
 * You are forewarned
 */
void init_processer(int last)
{
    p_conf.init = 1;
    p_conf.k = 0;
    p_conf.last = last;

}

void send_signal_to_indexer(){

    pthread_mutex_lock(&mutex_shared);
    if(DEBUGPTH)
        printf("Avisant a l'indexer que ya han terminat els procesadors\n");
    ibuffer->end = 1;

    pthread_cond_signal(&cond_indexar);
    pthread_mutex_unlock(&mutex_shared);

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
    //Indexer_buffer *indexer_buffer = ibuffer;
    Str_array *arxius = context->llista;
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
        // asignar el numero de fichero procesado
        arxiu_procesat->number = narxiu;
        arxiu_procesat->totalarxius = arxius->length;

        // ExclusiON
        pthread_mutex_lock(&mutex_shared);

        if(DEBUGPTH){
            printf("Thread %i termina d'indexar\n",(int)tid);
        }

        while(ibuffer->quantity == ibuffer->length)
        {
            if(DEBUGPTH){
                printf("Buffer ple, thread %i espera\n",(int)tid);
            }
            pthread_cond_wait( &cond_procesar, &mutex_shared );
        }

        ibuffer->buffer[ ibuffer->pposition++ ] = arxiu_procesat;
        ibuffer->pposition %= ibuffer->length;
        ibuffer->quantity++;

        // usamos signal para despertar solo a un  hilo
        pthread_cond_signal(&cond_indexar);
        // liberamos la llave
        pthread_mutex_unlock(&mutex_shared);
        // ExclusiOFF

        fclose(fl);
        //free_hash_list(arxiu_procesat);
        //free(arxiu_procesat);
    }

    return NULL;
}
