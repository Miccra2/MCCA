#ifndef __LIST_H__
#define __LIST_H__

#include <stdlib.h>
#include <stddef.h>

typedef struct _LISTNODE {
    struct _LISTNODE *node;
    size_t size;
    char buffer[];
} LISTNODE;

typedef struct _LIST {
    size_t length;
    LISTNODE *node;
} LIST;

LISTNODE *lnCreate(void *buffer, size_t size);
void lnDelete(LISTNODE **node);

void lDelete(LIST *list);

LISTNODE *lIndex(LIST *list, size_t index);

void lPrepend(LIST *list, LISTNODE *node);
void lAppend(LIST *list, LISTNODE *node);
void lInsert(LIST *list, LISTNODE *node, size_t index);

void lDequeue(LIST *list);
void lPop(LIST *list);
void lRemove(LIST *list, size_t index);

#endif // __LIST_H__
