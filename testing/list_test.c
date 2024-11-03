#include <list.h>
#include <stdio.h>
#include "assert.h"

int main() {
    LIST *list;
    LISTNODE *node;
    long int A, B, C;
    int ERRORCODE = 0;

    // list initialization
    list = lCreate();
    ASSERT(list != NULL,       "lCreate:0: list != NULL");
    ASSERT(list->length == 0,  "lCreate:1: list->length == 0");
    ASSERT(list->node == NULL, "lCreate:2: list->node == NULL");

    // list deletion
    lDelete(&list);
    ASSERT(list == NULL, "lDelete:0: list == NULL");

    A = 69;
    B = 420;
    C = 3001;
    
    // list node initialization
    node = lnCreate(&A, sizeof(A));
    ASSERT(node != NULL,                     "lnCreate:A:0: node != NULL");
    ASSERT(node->node == NULL,               "lnCreate:A:1: node->node == NULL");
    ASSERT(node->size == sizeof(A),          "lnCreate:A:2: '%i': node->size == sizeof(A)", node->size);
    ASSERT(node->buffer != NULL,             "lnCreate:A:3: node->buffer != NULL");
    ASSERT(*((long int *)node->buffer) == A, "lnCreate:A:4: '%i': *(node->buffer) == A", *((long int *)node->buffer));

    // list node deletion
    lnDelete(&node);
    ASSERT(node == NULL, "lnDelete:0: node == NULL");

    list = lCreate();

    // list prepend, append and insert
    lPrepend(list, &A, sizeof(A));
    lAppend(list, &B, sizeof(B));
    lInsert(list, 2, &C, sizeof(C));
    ASSERT(list->length == 3, "lPrepend:0: lAppend:1: lInsert:2: list->length == 3");

    // list index
    node = lIndex(list, 0);
    ASSERT(node == list->node,             "lIndex:0: 0x%.16X list[0]", node);
    node = lIndex(list, 1);
    ASSERT(node == list->node->node,       "lIndex:1: 0x%.16X list[1]", node);
    node = lIndex(list, 2);
    ASSERT(node == list->node->node->node, "lIndex:2: 0x%.16X list[2]", node);
    node = NULL;

ASSERTED:
    if (list) lDelete(&list);
    if (node) lnDelete(&node);
    return ERRORCODE;
}
