#include <stdio.h>
#include "view.h"

/**
 * Funcions que es poden cridar de la llibreria main
 */
func funcionalitat[ NFUNCTIONS ] = {
    create_data,
    store_data,   //TODO
    restore_data,   //TODO
    show_graphics,    //TODO
    NULL //sortir no es funcio
};

/**
 * Opcions que es mostran per indicar quina funcionalitat
 * es vol utilitzar
 */
char *labels[ NFUNCTIONS ] = {
    "Crear arbre",
    "Dessar arbre",
    "Llegir arbre",
    "Generar grafica",
    "Sortir"
};

/*
 * Show the available options
 */
void show_options()
{
    int option;

    

    printf("||\t\t\t\t\t\t\n"
            "||\t\t\t%s\n"
            "||\t\t\t\t\t\t\n"
            "||\t\t\t\t\t\t%s\n"
            , _NOMBRE_PRACTICA, _CREATORS);

    for(option = 0; option < NFUNCTIONS; option++)
    {
        printf("\t(%d) %s\n", (option + OPTION_OFFSET), labels[option]);
    }

}

/*
 * Get the selected option
 */
int get_option()
{

    int opcion;
    
    show_options();
    printf("\n%s\n", _ME_INPUT);

    scanf("%d", &opcion);
    opcion -= OPTION_OFFSET;
    while( opcion < 0 || opcion >= NFUNCTIONS )
    {
        printf("%s\n", _ER_INPUT);
        printf("%s", _ME_INPUT);
        scanf("%d", &opcion);
        opcion -= OPTION_OFFSET;
    }
    return opcion;
}

/*
 * The app main menu
 */
void menu_principal()
{
    int option;
    char file[MAX_PATH_LENGTH];

    deploy();

    option = get_option();
    
    while(option != SORTIR)
    {
        switch(option)
        {
            case CREAR_ARBRE:
                printf("%s\n", _ME_ARXIU_CFG);
                scanf("%s", file);
                if(tree_loaded())
                {
                    printf("%s\n", _ME_ESBORRANT_TREE);
                    freeall();
                    deploy();
                }
                (funcionalitat[option])(file);
            break;

            case DESSAR_ARBRE:
                if(!tree_loaded())
                {
                    printf("%s\n", _ER_FALTA_ARBRE_DESAR);
                }
                else
                {
                    printf("%s\n", _ME_ARXIU_GENERAR);
                    scanf("%s", file);
                    (funcionalitat[option])(file);
                }
            break;

            case LLEGIR_ARBRE:
                printf("%s\n", _ME_ARXIU_CARREGAR);
                scanf("%s", file);
                
                if(tree_loaded())
                {
                    printf("%s\n", _ME_ESBORRANT_TREE);
                    freeall();
                    deploy();
                }

                if((funcionalitat[option])(file))
                {
                    printf("%s\n", _ER_ARXIU_NOCOMPATIBLE);
                }
            break;

            case GENERAR_GRAFICA:
                if(!tree_loaded())
                    printf("%s\n", _ER_FALTA_ARBRE_GRAFICA);
                else
                    (funcionalitat[option])();
            break;
        }
        option = get_option();
    }

    freeall();
    printf("%s\n", _ME_BYE);
}

