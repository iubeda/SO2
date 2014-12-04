#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "include/const.h"
#include "include/functions.h"
#include "view.h"
#include "file-list.h"
#include "file-parser.h"
#include "linked-list.h"
#include "hash-list.h"
#include "red-black-tree.h"
#include "processer.h"
#include "indexer.h"


RBTree *tree;

pthread_t ntid[NTHREADS];


/**
 *
 * @arg: estructura del tipo pthread_processer con la informacion necesaria (arxiu, tree)
 *
 *
 */
/*
static void processador(void *arg)
{
    struct Processer_context *par = (struct Processer_context *) arg;
    int i,n, numarxius;
    FILE *fl;
    Hash_list *arxiu_procesat;

    numarxius = par->arxius->length;

    // recorrem el llistat d'arxius
    while( n == pnext() )
    {
        fl = fopen(par->arxius->data[i], "r");
        // si no podem obrir l'arxiu, pasem al seguent
        if(!fl) continue;
        arxiu_procesat = fparser(fl);

    //pthread_mutex_lock(&mutex);
        // un cop tenim l'arxiu procesat en una hash_list, l'indexem
        indexar_en_llista_global(par->tree, arxiu_procesat, par->arxius->length,  i);
    //pthread_mutex_unlock(&mutex);

        fclose(fl);

        // alliberem memoria
        free_hash_list(arxiu_procesat);
        free(arxiu_procesat);

    }
}
*/


/**
 * procesa un llistat d arxius
 * @ arxius : estructura tipus Str_array que conte un array de punters a string
 *              i la longitud de l'array
 * @ tree : arbre on s'indexaran els arxius
 */
static int processar_llista_arxius(Str_array *arxius, RBTree *tree)
{
    int n, i, err;
    void *tret;
    Processer_context *par;
    n = 0;

    par = malloc(sizeof(Processer_context));

    par->llista = arxius;
    par->tree = tree;

    // calls the function init processer
    init_processer(arxius->length);

    while(n < NTHREADS){

        /*
        *
        */
        err = pthread_create(ntid + n, NULL, procesador, (void *) par);
        if (err != 0) {
            printf("no puc crear el fil numero %d.", n);
            exit(1);
        }
        n++;
    }

    for(i = 0; i < NTHREADS; i++) {
        err = pthread_join(ntid[i], &tret);
        if (err != 0) {
            printf("error pthread_join al fil %d\n", i);
            exit(1);
        }
    }

    free(par);
    return 0;
}

/**
 * Funcio que crea l'estructura principal
 * s la funcio principal en la creacio de l'arbre. Un cop es crida aquesta
 * funcio, les altres es van cridant desde dins d'aquesta.
 * @ path : arxiu de configuracio amb la ruta dels arxius a parsejar
 */
int create_data(char *path)
{

    Str_array *paraules;
    int iter;
    Longest *maslarga;
    maslarga = tree->properties->longest;


    /* cridem a la funcio del llistat de paraules que retorna un struct */
    paraules = flist(path);
    processar_llista_arxius(paraules, tree);
    tree->config->loaded = 1;

    if(DEBUG)
    {
        dumpTree(tree);
        printf("Palabra mas larga: %s\n"
            "de longitud: %i\naparece en el fichero: %s\n",
            maslarga->word, maslarga->length, paraules->data[maslarga->file]);
    }
    // de moment podem eliminar les dades del arxiu de configuracio
    // aqui
    for(iter = 0; iter < paraules->length; iter++)
    {
        free(paraules->data[iter]);
    }
    free(paraules->data);
    free(paraules);

    return 0;
}

/**
 * Stores the tree in memory
 * @ path : arxiu de en el que guardar l'arbre en format binari
 */
int store_data(char *path)
{
    FILE *fl;
    int msize = MAGIC_NUMBER_SIZE;
    const char *magic = MAGIC_NUMBER;

    // identificador del nostre tipus d'arxiu
    fl = fopen(path, "w");
    fwrite(magic, sizeof(char), msize, fl);

    serializeTree(tree, fl);
    fclose(fl);
    return 0;
}

/**
 * Stores the tree in memory
 * @ path : arxiu del cual llegir l'arbre en format binari
 */
int restore_data(char *path)
{
    FILE *fl;
    int msize = MAGIC_NUMBER_SIZE;
    char *fmagic;
    const char *magic = MAGIC_NUMBER;

    fmagic = malloc(sizeof(char) * msize);
    fl = fopen(path, "r");
    fread(fmagic, sizeof(char), msize, fl);

    // file no compatible
    if(strncmp(magic, fmagic, msize) != 0 )
    {
        free(fmagic);
        fclose(fl);
        return 1;
    }

    deserializeTree(tree, fl);
    tree->config->loaded = 1;

    free(fmagic);
    fclose(fl);

    if(DEBUG)
    {
        printf("RESTORE\n");
        dumpTree(tree);
    }
    return 0;
}

/**
 * Funcio que genera una grafica que representa l'hisograma de
 * l'arbre
 *
 */
int show_graphics(){
    FILE *fp;

    // Generamos los datos necesarios para el histograma
    if(!tree->properties->histogram->loaded)
    {
        generateHistogram(tree);

        fp = fopen(HISTOGRAM_FILE, "w");
        writeHistogram(tree, fp);
        fclose(fp);
    }


    fp = popen("gnuplot", "w");
    //fprintf(fp, "set term svg\n"); // formato salida
    //fprintf(fp, "set out 'grafico.svg'\n"); // archivo salida
    fprintf(fp, "set terminal x11 persist\n");
    fprintf(fp, "plot '%s' with lines\n", HISTOGRAM_FILE); // comando
    fflush(fp);

    pclose(fp);

    return 0;
}

/**
 * Funcio que retorna si l'arbre esta carregat a memoria o no
 */
int tree_loaded()
{
    return tree->config->loaded;
}

/**
 * Funcio que fa malloc de les estructures principals de l'aplicacio
 */
void deploy()
{
    // iniciamos el arbol
    tree = malloc(sizeof(RBTree));
    initTree(tree);
}

/**
 * Funcio que allibera els recursos principals de l'aplicacio
 */
void freeall()
{

    deleteTree( tree );
    free(tree);
}
/**
 *
 * Main function
 *
 */
int main()
{
    menu_principal();

    return 0;
}
