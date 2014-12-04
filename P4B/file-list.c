#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file-list.h"
#include "include/const.h"

/**
 * Funcio que llegeix un arxiu i retorna una structura tipus str_array amb les lines
 * @ fname : nom del arxiu a procesar
 */
Str_array *flist(char *fname)
{
    char str[MAX_PATH_LENGTH];

    //iSList paraules; //llista de paraules
    //s_init(&paraules); //inicialitzem

    FILE *fp;
    int num_files, counter, len;
    char **files;
    Str_array *paraules;
    paraules = (Str_array *) malloc(sizeof(Str_array));

    fp = fopen(fname, "r");
    if (!fp) {
        printf("No he pogut obrir %s.\n", fname);
        exit(1);
    }

    fscanf(fp, "%d", &num_files);// la primera linea es el numero de linies
    files = malloc(sizeof(char*) * num_files); //fem malloc

    for(counter = 0; counter < num_files; counter++)
    {
        fscanf(fp, "%s", str); // leemos el caracter
        len = strlen(str); // recuperamos su longitud
        files[counter] = malloc( sizeof(char) * (len + 1)); // allocatamos
        strcpy(files[counter], str);
        //printf("added %s\n", files[counter]);
    }
    fclose(fp);

    //printf("Total files : %i\n", num_files);
    //printf("Primera paraula: %s\n", files[0]);

    paraules->length = num_files;
    paraules->data = files;

    //for(counter = 0; counter < num_files; counter++)
    //    free(files[counter]);
    //free(files);
    return paraules;
}
