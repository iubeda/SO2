/**
 *
 * Red-black tree implementation. 
 * 
 * Binary search trees work best when they are balanced or the path length from
 * root to any leaf is within some bounds. The red-black tree algorithm is a
 * method for balancing trees. The name derives from the fact that each node is
 * colored red or black, and the color of the node is instrumental in
 * determining the balance of the tree. During insert and delete operations,
 * nodes may be rotated to maintain tree balance. Both average and worst-case
 * search time is O(lg n).
 *
 * This implementation is original from John Morris, University of Auckland, at
 * the following link
 *
 * http://www.cs.auckland.ac.nz/~jmor159/PLDS210/niemann/s_rbt.htm
 *
 * and has been adapted here by Lluis Garrido, 2014.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "red-black-tree.h"


void initRBData(RBData *data, int len_primary_key, int num_files)
{
    int i;
    data->primary_key = malloc( sizeof(char) * ( len_primary_key + 1) );
    data->numTimes = malloc(sizeof(int) * num_files);
    data->numFiles = 0; // numero d'arxius en els que surt
    data->total_= num_files; //numero d'arxius totals
    // posem totes les posicions del vector a 0
    for(i=0; i<num_files; i++)
    {
        data->numTimes[i] = 0;
    }
}

/**
 * P2:
 * Imprime los datos
 */
static void dumpRBData(RBData *data)
{
    int extended = 0;
    int iter, num_times;
    num_times = 0;
    for(iter = 0; iter < data->total_; iter++)
    {
        num_times += data->numTimes[iter];
    }
    if(extended)
    {
        printf("Primary key\t %s\n", data->primary_key);
        printf("NumFiles\t %i\n", data->numFiles);
        printf("[");
        for(iter = 0; iter < data->total_; iter++)
        {
            printf("%i,", data->numTimes[iter]);
        }
        printf("] : %i\n", num_times);

    }
    else
    {
        printf("(%i, %s)\n", num_times, data->primary_key);
    }
}
/**
 *
 * Free data element. The user should adapt this function to their needs.  This
 * function is called internally by deleteNode.
 *
 */

static void freeRBData(RBData *data)
{
    /*P2: Liberamos el vector de cantidades, la primary key  y el struct*/
    free(data->numTimes);
    free(data->primary_key);
    free(data);
}

/**
 *
 * Compares if primary_key1 is less than primary_key2. Should return 1 (true) if condition
 * is satisfied, 0 (false) otherwise.
 *
 */

static int compLT(TYPE_RBTREE_PRIMARY_KEY *primary_key1, TYPE_RBTREE_PRIMARY_KEY *primary_key2)
{
    /*P2: al modificar el tipo de la PK debemos modificar esta funcion
     http://stackoverflow.com/questions/18408558/logic-challenge-sorting-arrays-alphabetically-in-c
     */
    int rc = strcmp(primary_key1, primary_key2) < 0 ? 1 : 0;
    return rc;
}

/**
 *
 * Compares if primary_key1 is equal to primary_key2. Should return 1 (true) if condition
 * is satisfied, 0 (false) otherwise.
 *
 */

static int compEQ(TYPE_RBTREE_PRIMARY_KEY *primary_key1, TYPE_RBTREE_PRIMARY_KEY *primary_key2)
{
    /*P2: al modificar el tipo de la PK debemos modificar esta funcion */
    int rc = strcmp(primary_key1, primary_key2) == 0 ? 1 : 0;
    return rc;
}

/**
 * 
 * PLEASE DO NOT CHANGE THE CODE BELOW UNLESS YOU REALLY KNOW WHAT YOU ARE
 * DOING.
 *
 */

#define NIL &sentinel           /* all leafs are sentinels */
static Node sentinel = { NIL, NIL, 0, BLACK, NULL};

/**
 *
 * Initialize the tree.
 * 
 *
 */

void initTree(RBTree *tree)
{
  tree->root = NIL;
}

/**
 *
 *  Rotate node x to left. Should not be called directly by the user. This
 *  function is used internally by other functions.
 *
 */

static void rotateLeft(RBTree *tree, Node *x) {

  Node *y = x->right;

  /* establish x->right link */
  x->right = y->left;
  if (y->left != NIL) y->left->parent = x;

  /* establish y->parent link */
  if (y != NIL) y->parent = x->parent;
  if (x->parent) {
    if (x == x->parent->left)
      x->parent->left = y;
    else
      x->parent->right = y;
  } else {
    tree->root = y;
  }

  /* link x and y */
  y->left = x;
  if (x != NIL) x->parent = y;
}

/**
 *  
 *  Rotate node x to right. Should not be called directly by the user. This
 *  function is used internally by other functions.
 *
 */

static void rotateRight(RBTree *tree, Node *x) {
  Node *y = x->left;

  /* establish x->left link */
  x->left = y->right;
  if (y->right != NIL) y->right->parent = x;

  /* establish y->parent link */
  if (y != NIL) y->parent = x->parent;
  if (x->parent) {
    if (x == x->parent->right)
      x->parent->right = y;
    else
      x->parent->left = y;
  } else {
    tree->root = y;
  }

  /* link x and y */
  y->right = x;
  if (x != NIL) x->parent = y;
}

/** 
 *
 * Maintain Red-Black tree balance  after inserting node x. Should not be
 * called directly by the user. This function is used internally by other
 * functions.
 *
 */

static void insertFixup(RBTree *tree, Node *x) {
  /* check Red-Black properties */
  while (x != tree->root && x->parent->color == RED) {
    /* we have a violation */
    if (x->parent == x->parent->parent->left) {
      Node *y = x->parent->parent->right;
      if (y->color == RED) {

	/* uncle is RED */
	x->parent->color = BLACK;
	y->color = BLACK;
	x->parent->parent->color = RED;
	x = x->parent->parent;
      } else {

	/* uncle is BLACK */
	if (x == x->parent->right) {
	  /* make x a left child */
	  x = x->parent;
	  rotateLeft(tree,x);
	}

	/* recolor and rotate */
	x->parent->color = BLACK;
	x->parent->parent->color = RED;
	rotateRight(tree, x->parent->parent);
      }
    } else {

      /* mirror image of above code */
      Node *y = x->parent->parent->left;
      if (y->color == RED) {

	/* uncle is RED */
	x->parent->color = BLACK;
	y->color = BLACK;
	x->parent->parent->color = RED;
	x = x->parent->parent;
      } else {

	/* uncle is BLACK */
	if (x == x->parent->left) {
	  x = x->parent;
	  rotateRight(tree, x);
	}
	x->parent->color = BLACK;
	x->parent->parent->color = RED;
	rotateLeft(tree,x->parent->parent);
      }
    }
  }
  tree->root->color = BLACK;
}

/**
 *  
 * Allocate node for data and insert in tree. This function does not perform a
 * copy of data when inserting it in the tree, it rather creates a node and
 * makes this node point to the data. Thus, the contents of data should not be
 * overwritten after calling this function.
 *
 */

void insertNode(RBTree *tree, RBData *data) {
  Node *current, *parent, *x;

  /* Find where node belongs */
  current = tree->root;
  parent = 0;
  while (current != NIL) {
    if (compEQ(data->primary_key, current->data->primary_key)) {
      printf("insertNode: trying to insert but primary key is already in tree.\n");
      exit(1);
    }
    parent = current;
    current = compLT(data->primary_key, current->data->primary_key) ?
      current->left : current->right;
  }

  /* setup new node */
  if ((x = malloc (sizeof(*x))) == 0) {
    printf ("insufficient memory (insertNode)\n");
    exit(1);
  }

  /* Note that the data is not copied. Just the pointer
     is assigned. This means that the pointer to the 
     data should not be overwritten after calling this
     function. */

  x->data = data;

  /* Copy remaining data */
  x->parent = parent;
  x->left = NIL;
  x->right = NIL;
  x->color = RED;

  /* Insert node in tree */
  if(parent) {
    if(compLT(data->primary_key, parent->data->primary_key))
      parent->left = x;
    else
      parent->right = x;
  } else {
    tree->root = x;
  }

  insertFixup(tree, x);
}

/**
 *
 *  Find node containing the specified primary_key. Returns the node.
 *  Returns NULL if not found.
 *
 */

RBData *findNode(RBTree *tree, TYPE_RBTREE_PRIMARY_KEY *primary_key) {

  Node *current = tree->root;
  while(current != NIL)
    if(compEQ(primary_key, current->data->primary_key))
      return (current->data);
    else
      current = compLT(primary_key, current->data->primary_key) ?
	current->left : current->right;

 return NULL;
}

/**
 *
 *  Function used to delete a tree. Do not call directly. 
 *
 */

static void deleteTreeRecursive(Node *x)
{
  if (x->right != NIL)
    deleteTreeRecursive(x->right);

  if (x->left != NIL)
    deleteTreeRecursive(x->left);

  freeRBData(x->data);
  free(x);
}


/**
 *
 *  Delete a tree. All the nodes and all the data pointed to by
 *  the tree is deleted. 
 *
 */

void deleteTree(RBTree *tree)
{
  if (tree->root != NIL)
    deleteTreeRecursive(tree->root);
}


/**
 *  P2:
 *  Function used to dump a tree. Do not call directly. 
 *
 */

static void dumpTreeRecursive(Node *x)
{
  if (x->right != NIL)
    dumpTreeRecursive(x->right);

  if (x->left != NIL)
    dumpTreeRecursive(x->left);

  dumpRBData(x->data);
}


/**
 *  P2:
 *  Dump a tree. All the nodes and all the data pointed to by
 *  the tree is deleted. 
 *
 */

void dumpTree(RBTree *tree)
{
  if (tree->root != NIL)
    dumpTreeRecursive(tree->root);
}
