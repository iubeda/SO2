#ifndef _FILE_LIST_H
#define _FILE_LIST_H
#include "include/const.h"

typedef struct STRING_ARRAY{
    int length; // longitud del vector
    char **data; // datos
}Str_array;

Str_array *flist(char *fname);

#endif
