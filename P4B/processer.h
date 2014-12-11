#ifndef _PROCESSER_H
#define _PROCESSER_H
#include "include/const.h"
#include "file-list.h"
#include "hash-list.h"
#include "red-black-tree.h"

typedef struct _PROCESSER_CONTEXT{
    Str_array *llista;
    RBTree *tree; // no necesari
}Processer_context;


typedef struct _PROCESSER_CONF{
    int init;   // defines if the processer is configured
    int k;      // the element to be processed
    int last;   // the last element to be processed
}Processer_conf;

void init_processer(int limit);
void *procesador(void *arg);

#endif
