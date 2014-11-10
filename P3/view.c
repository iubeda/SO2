#include <stdio.h>
#include "view.h"


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
void menu()
{
    int option;
    char file[MAX_PATH_LENGTH];

    option = get_option();
    
    while(option != SORTIR)
    {
        switch(option)
        {
            case CREAR_ARBRE:
                
                printf("Donam el arxiu de configuracio:\n");
                scanf("%s", file);
                
                (funcionalitat[option])(file);

            break;
            case DESSAR_ARBRE:
            //TODO
            break;
            case LLEGIR_ARBRE:
            //TODO
            break;
            case GENERAR_GRAFICA:
            //TODO
            break;
        }
        option = get_option();
    }
    printf("BYE\n");
}

