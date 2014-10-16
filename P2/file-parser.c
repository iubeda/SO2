#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "file-parser.h"


/*
 *  Devuelve el hash de una palabra
 */
int hash( char *word ){
  unsigned int i, len, seed, sum, hash;

  len = strlen(word);
  sum = 0;
  seed = 131;
  for(i = 0; i < len; i++)
    sum = sum * seed + (int)word[i];

  hash = sum % MAX_ARRAY_LINKED_LISTS;

  return hash;
}



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
    // volquem la paraula amb strncpy, que ens permet definir la longitud a copiar
    strcpy(newword, word);
    // retornem el punter
    return newword;
}
/*
void alloclist(List *lista){
    
    lista = malloc(sizeof(List));
    initList(lista);
    
}
*/
/**
 * procesa una arxiu
 */
FILE *processar_arxiu(char *nom_arxiu)
{
    //TODO
    FILE *fl;
    
    // compruebo que existe el fichero
    fl = fopen(nom_arxiu, "r");
    if(!fl)
    {
        printf("No s'ha pogut obrir l'arxiu %s\n", nom_arxiu);
        return NULL;
    }
    return fl;
    
}


/**
 * Funcio que analitza un arxiu especificat per parametre
 * i emmagatzema les paraules valides en un array static.
 *
 * 
 */
List **fparser(char *nomarxiu)
{
    int i, currentbff, nwords,caracter, wordexception, hashvalue;
    int saveword;
    FILE *fl;
    char buffer[MAX_WORD_LENGTH];
    List **listaLocal;      // contindra 100 llistes enllacades
    List *listaEnllacada;
    ListData *nodo;         // primary_key -> palabra; numItems-> numero de coincidencias
    
    //Obrim el arxiu en mode lectura
    if( !(fl = processar_arxiu(nomarxiu)) )
    {
        return NULL;
    }

    for(i=0; i<MAX_ARRAY_LINKED_LISTS; i++){
        //alloclist(listaLocal[i]);
         listaLocal[i] = malloc(sizeof(List));
         initList(listaLocal[i]);
    }
    
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
            // TODO
            //
            // indexamos palabra en lista local (hash)
            buffer[currentbff] = ZERO;
            
            hashvalue = hash(buffer);
            
            listaEnllacada = listaLocal[hashvalue];
            
            nodo = findList(listaEnllacada, buffer);
            if(nodo){
                // la palabra existe previamente
                nodo->numTimes++;
                
            }else{
                // la palabra no existe, la creamos de cero
                nodo = malloc(sizeof(ListData));
                nodo->primary_key = allocword(buffer);
                nodo->numTimes = 1;

                insertList(listaEnllacada, nodo);
                
            }           
            
            saveword = 0;
            //words[nwords] = allocword(buffer, currentbff);
            currentbff = 0;
            nwords++;
        }
        caracter = fgetc(fl);

    }
    fclose(fl);

    //show_words(words, nwords);
    //free_words(words, nwords);

    return listaLocal;
}
