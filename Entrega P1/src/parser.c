#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// tamany maxim de paraula
#define MAXBUFFER 100
// tamany maxim de llistat de paraules, es podria solucionar amb una
// llista enllasada
#define MAXWORDS 1000
#define APOSTROFE '\''
#define ZERO '\0'



/*
 * Funcio que imprimeix una paraula per pantalla
 */
static void show_word(char *word)
{
    printf("Paraula valida: %s\n", word);
}

/*
 * Funcio que imprimeix un llistat de paraules
 */
static void show_words(char *words[], int nwords)
{
    int i = 0;
    while(i < nwords)
        show_word(words[i++]);

}

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
char *allocword(char word[], int len)
{
    char * newword;
    // allocatem len + 1 ja que len no inclueix el \0
    newword = malloc( (sizeof(char) * len) + 1 );
    // volquem la paraula amb strncpy, que ens permet definir la longitud a copiar
    strncpy(newword, word, len);
    // posem l'ultim carater a ZERO
    newword[len] = ZERO;
    // retornem el punter
    return newword;
}


/**
 * Funcio que analitza un arxiu especificat per parametre
 * i emmagatzema les paraules valides en un array static.
 *
 * 
 */
int aarxiu(char *nomarxiu)
{
    int currentbff, nwords,caracter, wordexception;
    int saveword;
    FILE *fl;
    char buffer[MAXBUFFER];
    char *words[MAXWORDS];
    
    //Obrim el arxiu en mode lectura
    fl = fopen(nomarxiu, "r");
    if(!fl)
    {
        printf("No s'ha pogut obrir l'arxiu");
        exit(1);
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

    while( !feof(fl) && nwords < MAXWORDS)
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
            saveword = 0;
            words[nwords] = allocword(buffer, currentbff);
            currentbff = 0;
            nwords++;
        }
        caracter = fgetc(fl);

    }
    fclose(fl);



    show_words(words, nwords);
    free_words(words, nwords);

    if(nwords == MAXWORDS)
    {
        printf("S'han enregistrat el maxim de paraules permeses\n");
    }
    printf("Paraules enregistrades: %i\n", nwords);
    return 0;
}
