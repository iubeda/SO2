#include <stdio.h>
#include "view.h"

/**
 * Funcions que es poden cridar de la llibreria main
 */
func funcionalitat[ NFUNCTIONS ] = {
    create_data,
    store_data,   //TODO
    restore_data,   //TODO
    NULL,    //TODO
    NULL //sortir no es funcio
};

/**
 * Opcions que es mostran per indicar quina funcionalitat
 * es vol utilitzar
 */
char *labels[ NFUNCTIONS ] = {
    "Crear arbre",
    "Dessar_arbre",
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

    char *header = "/**************************************************/\n"
        "/**************** SO2 - Practica 3 ****************/\n"
        "/**************************************************/\n";
    

    printf("%s", header);
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
    char *input_message = "\nSeleciona una opcio\n";
    
    show_options();
    printf("%s", input_message);

    scanf("%d", &opcion);
    opcion -= OPTION_OFFSET;
    while( opcion < 0 || opcion >= NFUNCTIONS )
    {
        printf("Opcio no valida\n");
        printf("%s", input_message);
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

    option = get_option();
    
    while(option != SORTIR)
    {
        switch(option)
        {
            case CREAR_ARBRE:
                printf("Arxiu de configuracio:\n");
                scanf("%s", file);
                (funcionalitat[option])(file);
            break;

            case DESSAR_ARBRE:
                printf("Arxiu a generar:\n");
                scanf("%s", file);
                (funcionalitat[option])(file);
            break;

            case LLEGIR_ARBRE:
                printf("Arxiu a llegir:\n");
                scanf("%s", file);
                
                if((funcionalitat[option])(file))
                {
                    printf("Arxiu no compatible\n");
                }
            break;

            case GENERAR_GRAFICA:
                //TODO
            break;
        }
        option = get_option();
    }
    printf("BYE\n");
}

