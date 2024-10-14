#include "list.h"

LISTNODE *lnCreate(void *buffer, size_t size) {
    LISTNODE *node = malloc(sizeof(LISTNODE) + size);
    node->node = NULL;
    node->size = size;

    for (size_t i = 0; i < size; i++) {
        node->buffer[i] = ((char *)buffer)[i];
    }

    return node;
}

void lnDelete(LISTNODE **node) {
    free(*node);
    *node == NULL;
}

void lDelete(LIST *list) {
    if (list->length > 0 && list->node == NULL)
        return;

    if (list->length == 1 && list->node != NULL)
        free(list->node);
        return;

    LISTNODE *dnode = list->node;
    LISTNODE *node = dnode->node;
    while (node != NULL) {
        free(dnode);
        dnode = node;
        node = node->node;
    }

    if (dnode != NULL) {
        free(dnode);
        dnode = NULL;
    }
}

LISTNODE *lIndex(LIST *list, size_t index) {
    if (list->length <= index || (list->node == NULL && list->length > 0)) {
        return NULL;
    }

    if (index == 0) {
        return list->node;
    }

    LISTNODE *node = list->node;
    for (size_t i = 0; i < index; i++) {
        if (node->node == NULL)
            return NULL;

        node = node->node;
    }

    return node;
}

void lPrepend(LIST *list, LISTNODE *node) {
    if (list->length > 0 && list->node == NULL)
        return;

    node->node = list->node;
    list->node = node;
    list->length++;
}

void lAppend(LIST *list, LISTNODE *node) {
    if (list->length > 0 && list->node == NULL)
        return;

    if (list->length == 0) {
        list->node = node;
        list->length++;
        return;
    }

    LISTNODE *lnode = lIndex(list, list->length - 1);

    if (lnode == NULL)
        return;

    lnode->node = node;
    list->length++;
}

void lInsert(LIST *list, LISTNODE *node, size_t index) {
    if (list->length > 0 && list->node == NULL)
        return;

    LISTNODE *lnode;
    if (index < 1)
        lnode = list->node;
    else
        lnode = lIndex(list, index - 1);
    
    if (lnode == NULL)
        return;
    
    node->node = lnode->node;
    lnode->node = node;
    list->length++;
}

void lDequeue(LIST *list) {
    if (list->length == 0 || (list->length > 0 && list->node == NULL))
        return;

    LISTNODE *dnode = list->node;
    list->node = dnode->node;

    free(dnode);
    dnode = NULL;

    list->length--;
}

void lPop(LIST *list) {
    if (list->length == 0 || (list->length > 0 && list->node == NULL))
        return;

    LISTNODE *dnode;
    if (list->length == 1) {
        dnode = list->node;
        list->node = NULL;
        
        free(dnode);
        dnode = NULL;
        
        list->length--;
        return;
    }
    
    dnode = lIndex(list, list->length - 2);
    
    if (dnode == NULL)
        return;

    free(dnode->node);
    dnode->node = NULL;

    list->length--;
}

void lRemove(LIST *list, size_t index) {
    if (list->length == 0 || (list->length > 0 && list->node == NULL))
        return;

    if (index == 0) {
        lDequeue(list);
        list->length--;
        return;
    }

    LISTNODE *node = lIndex(list, index - 1);
    if (node == NULL)
        return;

    LISTNODE *dnode = node->node;
    if (dnode == NULL)
        return;

    node->node = dnode->node;
    
    free(dnode);
    dnode = NULL;

    list->length--;
}
