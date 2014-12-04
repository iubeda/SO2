#ifndef _VIEW_H
#define _VIEW_H
#include "include/const.h"
#include "include/functions.h"
#define OPTION_OFFSET 1

#define _NOMBRE_PRACTICA "SO2 Practica 4"
#define _CREATORS "I.Ubeda && J.Marin"
#define _ME_INPUT "Selecciona una opcio:"
#define _ME_ARXIU_CFG "Indica una arxiu de configuracio:"
#define _ME_ESBORRANT_TREE "Esborrant arbre carregat previament"
#define _ME_ARXIU_GENERAR "Indica el nom del arxiu a generar"
#define _ME_ARXIU_CARREGAR "Indica el nom del arxiu a carregar"
#define _ME_BYE "BYE"

#define _ER_INPUT "Opcio no valida"
#define _ER_FALTA_ARBRE_DESAR "Has de tenir una arbre carregat per poder desar-ho"
#define _ER_ARXIU_NOCOMPATIBLE "L'arxiu indicat no es compatible"
#define _ER_FALTA_ARBRE_GRAFICA "Has de tenir un arbre carregat per generar la grafica"
void show_options();
int get_option();
void menu_principal();
extern char *labels[];
#endif
