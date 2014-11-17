#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H
#include "const.h"

#define NFUNCTIONS 5

#define CREAR_ARBRE 0
#define DESSAR_ARBRE 1
#define LLEGIR_ARBRE 2
#define GENERAR_GRAFICA 3
#define SORTIR 4

int create_data(char *path);
int store_data(char *path);
int restore_data(char *path);

void deploy();
void freeall();
int tree_loaded();

typedef int(*func)();
extern func funcionalitat[];
#endif
