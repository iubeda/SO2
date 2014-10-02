#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXBUFFER 100
#define MAXWORDS 1000
#define APOSTROFE '\''


static void show_word(char *word){
    printf("len: %d word: %s\n", (int)(strlen(word)), word);
}

static void show_words(char *words[], int nwords){
    int i = 0;
    while(i < nwords)
        show_word(words[i++]);

}

static void free_words(char *words[], int nwords){
    int i = 0;
    while(i < nwords)
        free(words[i++]);

}

/*
 * funcio que fa un malloc de la paraula en el array y retorna un punter
 */
char *allocword(char word[], int len){
    char * newword;
    // alocatamos len + 1 ya que no incluye el caracter \0
    newword = malloc( (sizeof(char) * len) + 1 );
    // volcamos la palabra con esta funcion, que le podemos indicar la longitud
    strncpy(newword, word, len);
    // ponemos el caracter \0 como ultimo
    newword[len] = '\0';
    // devolvemos el puntero
    return newword;
}


/**
 * Funcio que analitza un arxiu especificat per parametre
 */
int aarxiu(char *nomarxiu){
    int currentbff, nwords,caracter, numexception;
    int saveword;
    FILE *fl;
    char buffer[MAXBUFFER];
    char *words[MAXWORDS];
    
    //Obrim el arxiu en mode lectura
    fl = fopen(nomarxiu, "r");
    if(!fl){
        printf("No s'ha pogut obrir l'arxiu");
        exit(1);
    }

    // inicialitzem el contador del buffer
    currentbff = 0;
    numexception = 0;
    nwords = 0;
    saveword = 0;
    caracter = fgetc(fl);
    while( !feof(fl) ){
        if(isalpha(caracter)){ // comprobamos si es una letra
            // comprobamos que este en lowercase
            if(isupper(caracter)){
                caracter = tolower(caracter);
            }
            buffer[currentbff++] = caracter;
        }else if(isspace(caracter)){ // comprobamos si es un espacio o salto de linea
            // comprobamos que hay algo en el buffer
            if(currentbff){
                // comprobamos que el ultimo caracter no sea un '
                // si lo es, no lo tendremos en cuenta
                if(buffer[currentbff-1] == APOSTROFE) currentbff--;
            }
            // volvemos a comprobar que hay algo en el buffer
            if(currentbff && !numexception)
                saveword = 1;
            if(numexception){ 
                numexception = 0;
                currentbff = 0;

        }else if(isdigit(caracter)){ // comprobamos si es numero
            numexception = 1;
            currentbff = 0;
        }else if(ispunct(caracter)){
            if (caracter == APOSTROFE){
                if(currentbff){ // si hay caracteres en el buffer, guardamos este tmb
                    buffer[currentbff++] = caracter;
                }
            }else{
                saveword = 1;
            }
        }
        if(saveword && !numexception){
            saveword = 0;

            words[nwords] = allocword(buffer, currentbff);
            currentbff = 0;
            nwords++;
        }
        caracter = fgetc(fl);

    }
    fclose(fl);



    printf("Paraules enregistrades: %i\n", nwords);
    show_words(words, nwords);
    free_words(words, nwords);

    return 0;
}
