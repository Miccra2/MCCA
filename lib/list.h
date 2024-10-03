#ifndef __LIST_H__
#define __LIST_H__

#include <stdlib.h>
#include <stddef.h>

typedef struct _LISTNODE {
    struct _LISTNODE *node;
    size_t size;
    char buffer[];
} LISTNODE, *PLISTNODE;

typedef struct _LIST {
    size_t length;
    PLISTNODE node;
} LIST, *PLIST;

// list creating
PLIST lCreate(void);
PLISTNODE lCreateNode(size_t size, void *buffer);

// list deleting
size_t lDelete(PLIST *list);
size_t lDeleteNode(PLISTNODE *node);

// list accessing
PLISTNODE lIndex(PLIST list, size_t index);
char *lGet(PLIST list, size_t index);

// list lengthening
size_t lPrepend(PLIST list, size_t size, void *buffer);
size_t lAppend(PLIST list, size_t size, void *buffer);
size_t lInsert(PLIST list, size_t index, size_t size, void *buffer);

// list shortening
PLISTNODE lDequeue(PLIST list);
PLISTNODE lPop(PLIST list);
PLISTNODE lRemove(PLIST list, size_t index);

#endif // __LIST_H__
