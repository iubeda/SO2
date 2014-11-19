#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linked-string-list.h"
#include "include/const.h"


char *s_alloc(char word[])
{
    char *n_word;
    int len = strlen(word);
    n_word = malloc( sizeof(char) * (len + 1) );
    strcpy(n_word, word);
    //n_word[len] = ZERO;
    return n_word;
}

void s_add(SList *list, char *data)
{
   // printf("adding %s\n", data);
    
    SListItem *item;
    item = malloc(sizeof(SListItem));
    item->data = data;
    item->next = NULL;
    
    if(list->last)
    {
        // el ultimo item apunta al nuevo
        list->last->next = item;
        // el ultimo item es el nuevo
        list->last = item;
    }
    else
    { // es el primero
        list->last = item;
        list->first = item;
    }
    list->length++;
}


void s_push(SList *list, char *data)
{
    SListItem *item;
    item = malloc(sizeof(SListItem));
    item->data = data;
    if(list->first)
    {
        // el item apunta al primero
        item->next = list->first;
        // el primero es el item
        list->first = item;
    }
    else
    { // es el primero
        item->next = NULL;
        list->last = item;
        list->first = item;
    }
    list->length++;

}

void s_remove_first(SList *list)
{
    if(!list->first) return;
    SListItem *item;

    item = list->first;
    list->first = list->first->next;
    list->length--;
    free(item->data);
    free(item);
}

void s_remove_last(SList *list)
{
    if(!list->last)return;

    SListItem *item;
    item = list->first;
    
    while(item->next->next)
        item = item->next;

    list->last = item;
    list->length--;
    free(item->next->data);
    free(item->next);
}

void s_destroy(SList *list)
{

    while(list->first) s_remove_first(list);
//    if(list->first)
//    {
//        if(list->last) free(list->last);
//        SListItem *prev, *tmp;
//        tmp = list->first;
//
//        while(tmp->next)
//        {   
//            prev = tmp;
//            tmp = tmp->next;
//            free(prev->data);
//            free(prev);
//        }
//        free(list->first);
//    }
    //free(list);
}

void s_init(SList *list)
{
    //list = malloc(sizeof(list));
    list->length = 0;
    list->first = NULL;
    list->last = NULL;
}
