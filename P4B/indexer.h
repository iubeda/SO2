#ifndef _INDEXER_H
#define _INDEXER_H
#include "include/const.h"
#include "file-list.h"
#include "hash-list.h"
#include "red-black-tree.h"

void indexar_en_llista_global(RBTree *tree, Hash_list *aproc, int num_arxius,  int arxiu);

#endif 
