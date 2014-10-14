#ifndef _LINKED_STRING_LIST
#define _LINKED_STRING_LIST
/*
 * cabecera de la lista enlazada de strings
 */



// elemento de la lista
typedef struct SListItem_{
    struct SListItem_ *next;
    char *data;
}SListItem;

// lista
typedef struct SList_{
    int length;
    SListItem *first;
    SListItem *last;
}SList;

void s_init(SList *list);

// inserta al final
void s_add(SList *list, char *data);

//inserta al inicio
void s_push(SList *list, char *data);

// elimina y devuelve el inicio
void s_remove_first(SList *list);

// elimina y devuelve la posicion
//void remove(SList *list, int position);

// elimina y devuelve el ultimo
void s_remove_last(SList *list);

// elimina y libera memoria
void s_destroy(SList *list);

char *s_alloc(char word[]);
#endif
