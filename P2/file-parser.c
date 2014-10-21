#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "include/const.h"
#include "file-parser.h"
#include "hash-list.h"





/*
 * Funcio que imprimeix una paraula per pantalla
 */
/*
static void show_word(char *word)
{
    printf("Paraula valida: %s\n", word);
}
*/
/*
 * Funcio que imprimeix un llistat de paraules
 */
/*
static void show_words(char *words[], int nwords)
{
    int i = 0;
    while(i < nwords)
        show_word(words[i++]);

}
*/
/*
 * Funcio que allibera de memoria les paraules
 */
static void free_words(char *words[], int nwords)
{
    int i = 0;
    while(i < nwords)
        free(words[i++]);

}

/*
 * funcio que fa un malloc de la paraula en el array y retorna un punter
 */

char *allocword(char *word)
{
    int len;
    char * newword;
    len = strlen(word);
    // allocatem len + 1 ja que len no inclueix el \0
    newword = malloc( (sizeof(char) * len) + 1 );
    // volquem la paraula amb strcpy
    strcpy(newword, word);
    // retornem el punter
    return newword;
}


/**
 * Parsea un archivo y devuelve una hash list con todas las palabras
 */
Hash_list *fparser(FILE *fl)
{
    int i, currentbff, nwords,caracter, wordexception, hashvalue;
    int saveword;
    char buffer[MAX_WORD_LENGTH];
    
    Hash_list *llista_local;   // contindra 100 llistes enllacades
    List *llistaEnllacada;
    ListData *data;         // primary_key -> palabra; numItems-> numero de coincidencias
    

    llista_local = malloc(sizeof(Hash_list));
    llista_local->length = MAX_ARRAY_LINKED_LISTS;
    
    // iniciamos la hash list con tamano definido
    init_hash_list(llista_local);
    
    // inicialitzem el contador del buffer
    currentbff = 0;
    // identifica excepcio de paraula
    wordexception = 0;
    // numero de paraules valides
    nwords = 0;
    // identifica si hem d'emmagatzemar la paraula
    saveword = 0;
    // llegim el primer caracter
    caracter = fgetc(fl);

    while( !feof(fl))
    {
        if(isalpha(caracter)) // comprobem si es una lletra
        {
            if(!wordexception) // comprobem no tenim excepcio de paraula
            {
                if(isupper(caracter))
                {
                    caracter =  tolower(caracter);
                }
                // emmagatzemem la lletra
                buffer[currentbff++] = caracter;
            }
        }
        else if(isspace(caracter))
        {   // desactivem excepcio de numero
             wordexception = 0;
            // comprovem que hi han caracters al buffer
            if(currentbff)
            {
                // comprobem que l'ultim caracter no es apostrof
                // si ho es, l'eliminem
                if(buffer[currentbff-1] == APOSTROFE) 
                    currentbff--;
                // ara tornem a comprobar si n'hi han caracters
                if(currentbff)
                    saveword = 1;
            }
        }
        else if(isdigit(caracter))
        {
            // evitem paraula amb numeros al inici, final o enmig
            wordexception = 1;
            currentbff = 0;
        }
        else if(ispunct(caracter))
        {
            if (caracter == APOSTROFE && currentbff) // acceptem paraules amb apostrof
            {
                buffer[currentbff++] = caracter;
            }
            else if(currentbff) // Si no es apostrof no guardem el caracter pero si la paraula
            {
                saveword = 1;
            }
        }else
        {
            // si no es cap caracter conegut, el·liminem el buffer i activem excepcio
            wordexception = 1;
            currentbff = 0;
        }

        if(saveword)
        {
            // marcamos el final de la palabra en el buffer
            buffer[currentbff] = ZERO;
            // indexamos palabra en lista local (hash)
            hashvalue = hash_value(llista_local,buffer);
            // recuperamos la lista asociada a ese hash 
            llistaEnllacada = llista_local->data[hashvalue];
            // recuperamos el data de la lista asociada
            data = findList(llistaEnllacada, buffer);

            if(data){
                // la palabra existe previamente
                data->numTimes++;
            }else{
                /* La palabra no existe, creamos el data
                 * allocatamos la palabra, la apuntamos
                 * con el primary key y ponemos el numTimes a 1
                 */
                data = malloc(sizeof(ListData));
                data->primary_key = allocword(buffer);
                data->numTimes = 1;

                // insertamos el nuevo data
                insertList(llistaEnllacada, data);

            }

            saveword = 0;
            currentbff = 0;
            nwords++;
        }
        caracter = fgetc(fl);

    }

    //show_words(words, nwords);
    //free_words(words, nwords);

    return llista_local;
}
