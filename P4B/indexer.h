#ifndef _INDEXER_H
#define _INDEXER_H
#include "include/const.h"
#include "file-list.h"
#include "hash-list.h"
#include "red-black-tree.h"

void indexar_en_llista_global(RBTree *tree, Hash_list *aproc, int num_arxius,  int arxiu);
typedef struct _INDEXER_BUFFER{
    Hash_list *buffer;
    int end;        // final d'indexacio (se activa con barrera)
    int quantity;   // quantitat pendent d'indexar al buffer
    int iposition;  // posicio del seguent a indexar
    int pposition;  // posicio del seguent procesat
    int length;
}Indexer_buffer;

typedef struct _INDEXER_CONTEXT{
    RBTree *tree;
}Indexer_context;
Indexer_buffer *ibuffer;
#endif 
