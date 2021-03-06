#ifndef _RED_BLACK_TREE_H
#define _RED_BLACK_TREE_H

/**
 *
 * Red-black tree header 
 *
 * See red-black-tree.h for details.
 * 
 *
 */


#define TYPE_RBTREE_PRIMARY_KEY char /*P2: la clau ara es la propia paraula */



/**
 *
 * This structure holds the information to be stored at each node. Change this
 * structure according to your needs.  In order to make this library work, you
 * also need to adapt the functions compLT, compEQ and freeRBData. For the
 * current implementation the "primary_key" member is used to index data within the
 * tree. 
 *
 */

typedef struct RBData_
{
    // The variable used to index the tree has to be called "primary_key".
    // The type may be any you want (float, char *, etc)
    TYPE_RBTREE_PRIMARY_KEY *primary_key;     

    // This is the additional information that will be stored
    // within the structure.
    int *numTimes;   /*P2: informacion de cada archivo  */
    int numFiles;        /*P2: numero de archivos en los que sale */
    int total_; /*P2: numero total de archivos */
} RBData;

/**
 * Structure to with the longest word in the tree
 */
typedef struct LONGEST{
    int length; // longitud del la palabra
    int file;   // numero de fitxer
    char *word; // la palabra
}Longest;
/**
 * Structure for the histogram
 */
typedef struct HISTOGRAM_
{
    int loaded;
    int length;
    unsigned int *data;
}Histogram;

/*
 * Properties from the tree, created
 * during function executions, such as longest
 * word etc...
 */
typedef struct Properties_
{
    Longest *longest;
    Histogram *histogram;
}RBProperties;

/**
 * Configuration of the tree
 */
typedef struct RBDConf_
{
    int loaded;
}RBConf;

/**
*
 * The node structure 
 *
 */

typedef enum { BLACK, RED } nodeColor;

typedef struct Node_ {
    /* For internal use of the structure. Do not change. */
    struct Node_ *left;         /* left child */
    struct Node_ *right;        /* right child */
    struct Node_ *parent;       /* parent */
    nodeColor color;            /* node color (BLACK, RED) */

    /* Data to be stored at each node */
    RBData *data;                    /* data stored in node */
} Node;

/**
 *
 * The tree structure. It just contains the root node, from
 * which we may go through all the nodes of the binary tree.
 *
 */

typedef struct RBTree_ {
    RBConf *config;
    RBProperties *properties;
    Node *root;                   /* root of Red-Black tree */
} RBTree;

/* The extern declaration of the tree */
extern RBTree *tree;

/*
 * Function headers. Note that not all the functions of
 * red-black-tree.c have been included here.
 */

void initRBData(RBData *treeData, int len_primary_key, int num_files);
void initTree(RBTree *tree);
void insertNode(RBTree *tree, RBData *data);
RBData *findNode(RBTree *tree, TYPE_RBTREE_PRIMARY_KEY *primary_key); 
void deleteTree(RBTree *tree);
void dumpTree(RBTree *tree);
void serializeTree(RBTree *tree, FILE *fl);
void deserializeTree(RBTree *tree, FILE *fl);
void resetTree(RBTree *tree);
void generateHistogram(RBTree *tree);
void writeHistogram(RBTree *tree, FILE *fl);
#endif
