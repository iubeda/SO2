/**
 *
 * Main file 
 * 
 * This file calls the linked-list.c and red-black-tree.c function files.
 *
 * Lluis Garrido, 2014.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "linked-list.h"
#include "red-black-tree.h"

/**
 *
 *  Main function. Contains a simple example using both
 *  linked-list and red-black-tree.
 *
 */

int main(int argc, char **argv)
{
  int a, maxnum, ct;

  List list;
  ListData *listData;

  RBTree tree;
  RBData *treeData;

  if (argc != 2)
  {
    printf("Usage: %s maxnum\n", argv[0]);
    exit(1);
  }

  maxnum = atoi(argv[1]);

  printf("Test with linked-list\n");

  /* Random seed */
  srand(0);

  /* Initialize the list */
  initList(&list);

  for(ct = maxnum; ct; ct--) {
    /* Generate random key to be inserted in the tree */
    a = rand() % 100 + 1;

    /* Search if the key is in the tree */
    listData = findList(&list, a); 

    if (listData != NULL) {

      /* We increment the number of times current item has appeared */
      listData->numTimes++;
    } else {

      /* If the key is not in the list, allocate memory for the data and
       * insert it in the list */

      listData = malloc(sizeof(ListData));
      listData->primary_key = a;
      listData->numTimes = 1;

      insertList(&list, listData);
    }
  }

  printf("Printing contents of list:\n");
  /* Dump contents to stdout */
  dumpList(&list);

  /* Delete the list */
  deleteList(&list);

  printf("**********************************************************\n");

  printf("Test with red-black-tree\n");

  /* Random seed, same as before just to ensure that the same values are generated */
  srand(0);

  /* Initialize the tree */
  initTree(&tree);

  for (ct = maxnum; ct; ct--) {
    /* Generate random key to be inserted in the tree */
    a = rand() % 100 + 1;

    /* Search if the key is in the tree */
    treeData = findNode(&tree, a); 

    if (treeData != NULL) {

      /* If the key is in the tree increment 'num' */
      treeData->num++;
    } else {

      /* If the key is not in the tree, allocate memory for the data
       * and insert in the tree */

      treeData = malloc(sizeof(RBData));
      treeData->primary_key = a;
      treeData->string = malloc(sizeof(char) * 10);
      treeData->num = 1;

      insertNode(&tree, treeData);
    }
  }

  for(a = 0; a < 100; a++)
  {
    treeData = findNode(&tree, a);

    if (treeData) 
      printf("El numero %d apareix %d cops a l'arbre.\n", a, treeData->num);
  }
  
  /* Delete the tree */
  deleteTree(&tree);

  printf("Done.\n");

  return 0;
}

