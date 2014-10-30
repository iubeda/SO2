#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/const.h"
#include "file-list.h"
#include "file-parser.h"
#include "linked-list.h"
#include "hash-list.h"
#include "red-black-tree.h"

#define DEBUG 1
#define DUMP_LIST 0
#define DUMP_TREE 1


#define CREACION 1
#define GUARDAR 2
#define LEER 3
#define GRAFICA 4
#define SALIR 5


typedef struct LONGEST{
    int length; // longitud del la palabra
    int file;   // numero de fitxer
    char *word; // la palabra
}Longest;

Longest maslarga = {0, 0, NULL};



/**
 * Funcio que rep un tree i un arxiu procesar en format hash list 
 * i l'indexa
 * @ tree : arbre on s'indexa
 * @ aproc : arxiu procesat a indexar
 * @ fileid : numero d'arxiu a procesar
 * */
void indexar_en_llista_global(RBTree *tree, Hash_list *aproc, int num_arxius,  int arxiu)
{
    int i, len, j;
    RBData *treeData;
    ListItem *currentItem;
    ListData *data;

    
    // recorremos cada posicion de la lista hash
    for(i = 0; i < aproc->length; i++)
    {
        if(DUMP_LIST){
            printf("Dumping list %i, file %i\n", i, arxiu);
            dumpList(aproc->data[i]);
            printf("*\t*\t*\n");
        }
        //indexamos el contenido de esta lista enlazada
        //indexar_llista_enllasada(tree, aproc->data[i], aproc->length);

        //recuperem el primer node de la llista
        currentItem = aproc->data[i]->first;
        while(currentItem != NULL)
        {
            data = currentItem->data;
            //busquem la paraula a l'arbre
            treeData = findNode(tree, data->primary_key);
            if(treeData != NULL) // si la paraula esta a l'arbre
            {
                // augmentem en 1 el numero d'arxius en el que surt la paraula
                // i marquem el numero de cops que surt a l'arxiu
                treeData->numFiles++;
                treeData->numTimes[arxiu] = data->numTimes;

            }
            else
            {   
                // si no esta, hem d'allocatar, inicialitzar el data
                // copiar la paraula, copiar el numero de cops per arxiu
                // i aumengtar el numer d'arxus 
                treeData = malloc(sizeof(RBData));

                len = strlen(data->primary_key);
                initRBData(treeData, len,num_arxius);
                strcpy(treeData->primary_key, data->primary_key);
                treeData->numTimes[arxiu] = data->numTimes;
                treeData->numFiles++;
                insertNode(tree, treeData);
                
                
                // si esta palabra es mas larga que la almacenada como larga,
                // la guardamos
                if(maslarga.length < len)
                {
                    maslarga.length = len;
                    maslarga.file = arxiu; // solo almacena el primer archivo
                    maslarga.word = treeData->primary_key;
                }
                
            }
            currentItem = currentItem->next;

        }
    }
}

/**
 * procesa un llistat d arxius
 */
int processar_llista_arxius(Str_array *arxius, RBTree *tree)
{
    int i,j, numarxius;
    Hash_list *arxiu_procesat;

    numarxius = arxius->length;
    
    // recorrem el llistat d'arxius
    for( i = 0; i < numarxius; i++ )
    {
        FILE *fl;
        fl = fopen(arxius->data[i], "r");
        // si no podem obrir l'arxiu, pasem al seguent
        if(!fl) continue;

        arxiu_procesat = fparser(fl);
        // un cop tenim l'arxiu procesat en una hash_list, l'indexem
        indexar_en_llista_global(tree, arxiu_procesat, arxius->length,  i);

        fclose(fl);
        
        // alliberem memoria
        free_hash_list(arxiu_procesat);
        free(arxiu_procesat);

    }

}


int menu(){

    int opcion;
    
    printf("/**************************************************/\n");
    printf("/**************** SO2 - Practica 3 ****************/\n");
    printf("/**************************************************/\n");
    printf("    (1) Creacio de l'arbre\n");
    printf("    (2) Emmagatzema l'arbre\n");
    printf("    (3) Lectura d'un arbre\n");
    printf("    (4) Grafica\n");
    printf("    (5) Sortir\n");
    printf("/**************************************************/\n");
    printf("Selecciona una opcio:\n");
    scanf("%d",&opcion);
    
    return opcion;
}


/**
 *
 * Main function
 *
 */
int main()
{
    Str_array *paraules;
    RBTree tree;
    RBData *data;
    int iter, opt;
    char file[100];
   

    opt = menu();
    
    
    switch(opt){           // creacio de arbre
        
        case CREACION:
        
            printf("Donam el arxiu de configuracio:\n");
            scanf("%s", file);
            
            
            // iniciamos el arbol
            initTree(&tree);
            
            /* cridem a la funcio del llistat de paraules que retorna un struct */
            paraules = flist(file);
            processar_llista_arxius(paraules, &tree);
            
            
            if(DUMP_TREE) dumpTree(&tree);
        
            printf("Palabra mas larga: %s\n"
                "de longitud: %i\naparece en el fichero: %s\n",
                maslarga.word, maslarga.length, paraules->data[maslarga.file]);
        
        break;
        case GUARDAR:
        break;
        
        case LEER:
        break;
        
        case GRAFICA:
        break;
        
        case SALIR:
                    
            /* Delete the tree */
            deleteTree( &tree );
            
            // delete paraules
            for(iter = 0; iter < paraules->length; iter++)
            {
                free(paraules->data[iter]);
            }
            free(paraules->data);
            free(paraules);
            exit(1);
        break;
        
    }
    
    

    return 0;
}
