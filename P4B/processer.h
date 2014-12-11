#ifndef _PROCESSER_H
#define _PROCESSER_H
#include "include/const.h"
#include "file-list.h"
#include "hash-list.h"
#include "indexer.h"

typedef struct _PROCESSER_CONTEXT{
    Str_array *llista;
}Processer_context;


typedef struct _PROCESSER_CONF{
    int init;   // defines if the processer is configured
    int k;      // the element to be processed
    int last;   // the last element to be processed
}Processer_conf;

void init_processer(int limit);
void *procesador(void *arg);
void send_signal_to_indexer();

extern Indexer_buffer *ibuffer;
extern pthread_mutex_t mutex_shared;
extern pthread_cond_t cond_indexar;
extern pthread_cond_t cond_procesar;

#endif
