#ifndef HASH_LIST_H
#define HASH_LIST_H

#include "include/const.h"
#include "linked-list.h"


#define SEED 131

typedef struct HASH_LIST{
    int length; // longitud del vector
    List **data; // datos
}Hash_list;

void init_hash_list(Hash_list *list);
void free_hash_list(Hash_list *list);
int hash_value(Hash_list *list, char *word);

#endif
