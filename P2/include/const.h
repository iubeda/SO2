#ifndef _CONST_H
#define _CONST_H

#ifndef NULL
#define NULL (void *) 0 // esto estaba en SO1, y era util
#endif

#define MAX_PATH_LENGTH 250 // tamany maxim de path
#define MAX_WORD_LENGTH 100  // tamany maxim de paraula
#define APOSTROFE '\''
#define ZERO '\0'

typedef struct STRING_ARRAY{
    int length; // longitud del vector
    char **data; // datos
}STR_ARRAY;
#endif
