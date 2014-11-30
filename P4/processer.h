#ifndef _PROCESSER_H
#define _PROCESSER_H
#include "const.h"
#include "../file-list.h"
#include "../hash-list.h"
#include "../red-black-tree.h"

typedef struct _PTHREAD_PROCESSER{
    Hash_list *llista;
    RBTree *tree;
}PTHREAD_PROCESSER;


typedef struct _PROCESSER_CONF{
    int init;
    int k;
    int limit;
}PROCESSER_CONF;

int init_processer(int limit);
//int pnfext(Hash_list *llista); not public

#endif
