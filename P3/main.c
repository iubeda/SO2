#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/const.h"
#include "include/functions.h"
#include "view.h"
#include "file-list.h"
#include "file-parser.h"
#include "linked-list.h"
#include "hash-list.h"
#include "red-black-tree.h"


Longest maslarga = {0, 0, NULL};

func funcionalitat[ NFUNCTIONS ] = {
    crear_arbre,
    NULL,   //TODO
    NULL,   //TODO
    NULL,    //TODO
    NULL //sortir no es funcio
};

RBTree tree;


/**
 * Funcio que rep un tree i un arxiu procesar en format hash list 
 * i l'indexa
 * @ tree : arbre on s'indexar
 * @ aproc : arxiu procesat a indexar
 * @ num_arxius : numero dp'arxius total
 * @ arxiu : numero d'arxiu a procesar
 * */
static void indexar_en_llista_global(RBTree *tree, Hash_list *aproc, int num_arxius,  int arxiu)
{
    int i, len, j;
    RBData *treeData;
    ListItem *currentItem;
    ListData *data;

    
    // recorremos cada posicion de la lista hash
    for(i = 0; i < aproc->length; i++)
    {
        if(DEBUG){
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
 * @ arxius : estructura tipus Str_array que conte un array de punters a string 
 *              i la longitud de l'array
 * @ tree : arbre on s'indexaran els arxius
 */
static int processar_llista_arxius(Str_array *arxius, RBTree *tree)
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
 * Funcio que crea l'estructura principal
 * Es la funcio principal en la creacio de l'arbre. Un cop es crida aquesta
 * funcio, les altres es van cridant desde dins d'aquesta.
 * @ path : arxiu de configuracio amb la ruta dels arxius a parsejar
 */
void crear_arbre(char *path)
{

    Str_array *paraules;
    int iter;

    
    /* cridem a la funcio del llistat de paraules que retorna un struct */
    paraules = flist(path);
    processar_llista_arxius(paraules, &tree);
    
    
    if(DEBUG)
    {
        dumpTree(&tree);
        printf("Palabra mas larga: %s\n"
            "de longitud: %i\naparece en el fichero: %s\n",
            maslarga.word, maslarga.length, paraules->data[maslarga.file]);
    }
    // de moment podem eliminar les dades del arxiu de configuracio
    // aqui
    for(iter = 0; iter < paraules->length; iter++)
    {
        free(paraules->data[iter]);
    }
    free(paraules->data);
    free(paraules);
}
void deploy()
{
    // iniciamos el arbol
    initTree(&tree);
}
void freeall()
{
    deleteTree( &tree );
}
/**
 *
 * Main function
 *
 */
int main()
{
    deploy();

    menu();

    freeall();

    return 0;
}
