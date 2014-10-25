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


Longest maslarga = {0, 0, NULL};


/**
 * indexa una llista enllasada al tree
 */
//void indexar_llista_enllasada( RBTree *tree, List *hash_list, int numarxius)
//{
//    int pos, len;
//    RBData *treeData;
//    ListItem *current;
//
//    current = hash_list->first;
//
//    while (current != NULL)
//    {
//
//        if ( (treeData = findNode(  tree, current->data->primary_key)) )
//        {   // si hem trobat el node
//            
//            pos = treeData->num++;
//            treeData->string[pos] = current->data->numTimes;
//            
//        }else{
//            // If the key is not in the tree, allocate memory for the data
//            // and insert in the tree
//            
//            len = strlen(current->data->primary_key);
//            
//            treeData = malloc(sizeof(RBData));
//            // allocatamos el espacio necesario
//            treeData->primary_key = malloc( (sizeof(char) * len)+1 );
//            // copiamos la pk a treeData
//            strcpy(treeData->primary_key, current->data->primary_key);
//            treeData->string = malloc(sizeof(char) * numarxius);
//            treeData->string[0] = current->data->numTimes;
//            treeData->num = 1;
//
//            insertNode( tree, treeData );
//        }
//
//        current = current->next;
//    }
//}

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
            
           /* if(maslarga.length < strlen(data->primary_key)){
                maslarga.length = strlen(data->primary_key);
                maslarga.word = malloc( sizeof(char) * ( strlen(data->primary_key) + 1) );
                
                //strcpy(maslarga.word,data->primary_key);
            }
            */
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
                
                
                // si esta palabra es mas larga que la almacenada como larga, la guardamos
                if(maslarga.length < len)
                {
                    maslarga.length = len;
                    maslarga.file = arxiu;
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


/**
 *
 * Main function
 *
 */
int main(int argc, char **argv)
{
    Str_array *paraules;
    RBTree tree;
    RBData *data;
    //maslarga = malloc(sizeof(Longest));
    //maslarga.length = 0;
    //maslarga.word = NULL;
    
    /* comprobem si hi ha parametre d'entrada */
    if (argc != 2)
    {
        printf("Exemple d'us: %s fitxer.cfg\n", argv[0]);
        exit(1);
    }
    
    // iniciamos el arbol
    initTree(&tree);
    
    /* cridem a la funcio del llistat de paraules que retorna un struct */
    paraules = flist(argv[1]);
    processar_llista_arxius(paraules, &tree);


    // liberamos memoria
    int iter;
    for(iter = 0; iter < paraules->length; iter++)
    {
        free(paraules->data[iter]);
    }
    free(paraules->data);
    free(paraules);
    
    /*P2: testeo cutre del arbol*/
    //data = tree.root->right->data;  
    //printf("palabra: %s | puntero %p | numfiles: %i | info: %i | total %i \n", data->primary_key, data->primary_key, data->numFiles, data->numTimes[0], data->total_);
  
    /* Delete the tree */
    if(DUMP_TREE) dumpTree(&tree);
    
    printf("Palabra mas larga: word: %s | longitud: %i | fichero: %i\n", maslarga.word, maslarga.length, maslarga.file);
    
    deleteTree( &tree );
    //  free(maslarga);
    return 0;
}
