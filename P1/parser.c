#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXBUFFER 100
#define MAXWORDS 1000
#define APOSTROFE '\''
#define ZERO '\0'


static void show_word(char *word)
{
    printf("len: %d word: %s\n", (int)(strlen(word)), word);
}

static void show_words(char *words[], int nwords)
{
    int i = 0;
    while(i < nwords)
        show_word(words[i++]);

}

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
    // alocatamos len + 1 ya que no incluye el caracter \0
    newword = malloc( (sizeof(char) * len) + 1 );
    // volcamos la palabra con esta funcion, que le podemos indicar la longitud
    strncpy(newword, word, len);
    // ponemos el caracter \0 como ultimo
    newword[len] = ZERO;
    // devolvemos el puntero
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
    int currentbff, nwords,caracter, numexception;
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
    numexception = 0;
    nwords = 0;
    saveword = 0;
    caracter = fgetc(fl);
    while( !feof(fl) && nwords < MAXWORDS)
    {
        if(isalpha(caracter) && !numexception)
        { // comprobamos si es una letra y no hay numexceptin
            // comprobamos que este en lowercase
            if(isupper(caracter))
            {
                caracter = tolower(caracter);
            }
            buffer[currentbff++] = caracter;
        }
        else if(isspace(caracter))
        {   // desactivamos numexception si lo hubiese
            if(numexception)numexception = 0;
            // comprobamos que hay algo en el buffer
            if(currentbff)
            {
                // comprobamos que el ultimo caracter no sea un '
                // si lo es, no lo tendremos en cuenta
                if(buffer[currentbff-1] == APOSTROFE) currentbff--;
            }
            // volvemos a comprobar que hay algo en el buffer
            if(currentbff)
            {
                saveword = 1;
            }
        }
        else if(isdigit(caracter))
        {
            // comprobamos si es numero
            // evitamos palabra con numero al inicio, o en medio
            numexception = 1;
            currentbff = 0;
        }
        else if(ispunct(caracter))
        {
            if (caracter == APOSTROFE)
            {
                if(currentbff)
                { // si hay caracteres en el buffer, guardamos este tmb
                    buffer[currentbff++] = caracter;
                }
            }
            else if(currentbff)
            {
                saveword = 1;
            }
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
