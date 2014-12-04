#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash-list.h"


/**
 * Iniciamos una lista hash con la longitud que nos pasan por parametro
 *
 */
void init_hash_list(Hash_list *list)
{

    int i;
    // iniciamos la lista entera con List's
    list->data = malloc(sizeof(List*) * list->length);
    for(i = 0; i < list->length; i++)
    {
        // allocatamos e iniciamos cada elemento con un List
        list->data[i] = malloc(sizeof(List));
        initList(list->data[i]);
    }
}


/**
 * Libera cada elemento de la hash_list
 *
 * */
void free_hash_list(Hash_list *list)
{
    int i;
    for( i = 0; i < list->length; i++)
    {
        //liberamos
        deleteList(list->data[i]);
        free(list->data[i]);
    }
    //liberamos
    free(list->data);
}


int hash_value(Hash_list *list, char *word)
{
  unsigned int i, len, seed, sum, hash;

  len = strlen(word);
  sum = 0;
  seed = SEED;
  for(i = 0; i < len; i++)
    sum = sum * seed + (int)word[i];

  hash = sum % list->length;

  return hash;

}
