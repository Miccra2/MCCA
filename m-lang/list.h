#ifndef __LIST_H__
#define __LIST_H__

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct LISTNODE {
    struct LISTNODE *node;
    size_t size;
    char *buffer;
} LISTNODE;

typedef struct LIST {
    size_t length;
    LISTNODE *node;
} LIST;

// list creation
LIST *lCreate();
LISTNODE *lnCreate(void *buffer, size_t size);

// list deletion
int lDelete(LIST **list);
int lnDelete(LISTNODE **node);

// access list itmes
LISTNODE *lIndex(LIST *list, size_t index);
void *lGet(LIST *list, size_t index);
//size_t lIterate(LIST *list, bool (*function)(LISTNODE *));

// list growth
int lPrepend(LIST *list, void *buffer, size_t size);
int lAppend(LIST *list, void *buffer, size_t size);
int lInsert(LIST *list, size_t index, void *buffer, size_t size);

int lnPrepend(LIST *list, LISTNODE *node);
int lnAppend(LIST *list, LISTNODE *node);
int lnInsert(LIST *list, size_t index, LISTNODE *node);

// list shrinking
int lDequeue(LIST *list);
int lPop(LIST *list);
int lRemove(LIST *list, size_t index);

LISTNODE *lnDequeue(LIST *list);
LISTNODE *lnPop(LIST *list);
LISTNODE *lnRemove(LIST *list, size_t index);

#endif // __LIST_H__
