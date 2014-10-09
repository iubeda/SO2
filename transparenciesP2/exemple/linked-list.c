/**
 *
 * Linked-list implementation. 
 * 
 * This is an implementation of a simple linked-list. A minimal
 * set of necessary functions have been included.
 *
 * Lluis Garrido, 2014.
 *
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * We include the linked-list.h header. Note the double
 * quotes.
 */

#include "linked-list.h"

/**
 *
 * Free data element. The user should adapt this function to their needs.  This
 * function is called internally by deleteList.
 *
 */

static void freeListData(ListData *data)
{
  free(data); 
}

/**
 *
 * Dumps data contents to stdout. To be used for debugging.
 *
 */

static void dumpListData(ListData *data)
{
  printf("Key %03d appears %d times\n", data->primary_key, data->numTimes);
}

/**
 *
 * Compares if primary_key1 is equal to primary_key2. Should return 1 (true) if condition
 * is satisfied, 0 (false) otherwise.
 *
 */

static int compEQ(TYPE_LIST_PRIMARY_KEY primary_key1, TYPE_LIST_PRIMARY_KEY primary_key2)
{
  int rc = (primary_key1 == primary_key2);
  return rc;
}

/**
 * 
 * Please do not change the code below unless you really know what you are
 * doing.
 *
 */

/**
 * 
 * Initialize an empty list
 *
 */

void initList(List *l)
{
  l->numItems = 0;
  l->first = NULL;
}

/**
 * 
 * Insert data in the list.  This function does not perform a copy of data
 * when inserting it in the list, it rather creates a list item and makes
 * this item point to the data. Thus, the contents of data should not be
 * overwritten after calling this function.
 *
 */

void insertList(List *l, ListData *data)
{
  ListItem *tmp, *x;

  x = malloc(sizeof(ListItem));

  if (x == 0) {
    printf("insufficient memory (insertItem)\n");
    exit(1);
  }

  /* Insert item at first position */

  tmp = l->first;
  l->first = x;
  x->next = tmp;

  /* Link data to inserted item */
  x->data = data;

  l->numItems++;
}

/**
 * 
 * Find item containing the specified primary_key. Returns the data
 * that it points to (not the item itself).
 *
 */

ListData *findList(List *l, TYPE_LIST_PRIMARY_KEY primary_key)
{
  ListItem *current;

  current = l->first;

  while (current != NULL)
  {
    if (compEQ(current->data->primary_key, primary_key))
      return (current->data);

    current = current->next;
  }

  return (NULL);
}

/**
 * 
 * Deletes the first item of the list. The data to which
 * the deleted item points to also is deleted.
 *
 */

void deleteFirstList(List *l)
{
  ListItem *tmp;

  tmp = l->first;

  if (tmp)
  {
    l->first = tmp->next;
    freeListData(tmp->data);
    free(tmp);
    l->numItems--;
  }
}

/**
 * 
 * Deletes a list including the data to which their 
 * items point to.
 *
 */

void deleteList(List *l)
{
  ListItem *current, *next;

  current = l->first;

  while (current != NULL)
  {
    next = current->next;
    freeListData(current->data);
    free(current);
    current = next;
  }

  l->numItems = 0;
  l->first = NULL;
}

/**
 * 
 * Dumps the contents of the list. Internally this function
 * called dumpListData which is user defined.
 *
 */

void dumpList(List *l)
{
  ListItem *current;

  current = l->first;

  while (current != NULL)
  {
    dumpListData(current->data);
    current = current->next;
  }

  printf("Total number of items: %d\n", l->numItems);
}

