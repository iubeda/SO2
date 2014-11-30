#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include "const.h"
#include "../file-list.h"
#include "../hash-list.h"
#include "../red-black-tree.h"

#define NFUNCTIONS 5
#define CREAR_ARBRE 0
#define DESSAR_ARBRE 1
#define LLEGIR_ARBRE 2
#define GENERAR_GRAFICA 3
#define SORTIR 4

int create_data(char *path);
int store_data(char *path);
int restore_data(char *path);
int show_graphics();

void deploy();
void freeall();
int tree_loaded();

typedef int(*func)();
extern func funcionalitat[];

typedef struct PTHREAD_INDEXER{
    RBTree *tree;
    Hash_list *aproc;
    int num_arxius;
    int arxius;
}pthread_indexer;

#endif
