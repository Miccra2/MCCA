#include "list.h"

LIST *lCreate() {
    LIST *list = malloc(sizeof(LIST));
    list->length = 0;
    list->node = NULL;
    return list;
}

LISTNODE *lnCreate(void *buffer, size_t size) {
    LISTNODE *node = malloc(sizeof(LISTNODE));
    node->node = NULL;
    node->size = size;
    node->buffer = malloc(size);

    for (size_t i = 0; i < size; i++) {
        node->buffer[i] = ((char *)buffer)[i];
    }

    return node;
}

int lDelete(LIST **list) {
    if (list == NULL || *list == NULL) return 1;
    if ((*list)->node == NULL) {
        free(*list); 
        *list = NULL;
        return 0;
    }

    if ((*list)->length == 1) {
        free((*list)->node->buffer);
        free((*list)->node);
        free(*list);
        *list = NULL;
        return 1;
    }

    LISTNODE *node;
    LISTNODE *nnode = (*list)->node;

    while (nnode != NULL) {
        node = nnode;
        nnode = nnode->node;
        lnDelete(&node);
    }

    free(*list);
    *list = NULL;
    return 0;
}

int lnDelete(LISTNODE **node) {
    free((*node)->buffer);
    free(*node);
    *node = NULL;
    return 0;
}

LISTNODE *lIndex(LIST *list, size_t index) {
    LISTNODE *node;

    if ((index < 0) || (index > list->length) || (list == NULL) || (list->node == NULL)) return NULL;

    node = list->node;
    size_t i = 0;
    while (i < index && i < list->length && node->node != NULL) {
        node = node->node;
        i++;
    }
    if (i != index) return NULL;

    return node;
}

void *lGet(LIST *list, size_t index) {
    LISTNODE *node = lIndex(list, index);
    if (node == NULL) return NULL;
    return (void *)node->buffer;
}

int lPrepend(LIST *list, void *buffer, size_t size) {
    LISTNODE *node;

    if (list == NULL) return 1;

    node = lnCreate(buffer, size);
    node->node = list->node;
    list->node = node;

    list->length++;
    return 0;
}

int lAppend(LIST *list, void *buffer, size_t size) {
    LISTNODE *node;

    if (list == NULL) return 1;
    if (list->length == 0) {
        list->node = lnCreate(buffer, size);
        list->length++;
        return 0;
    }

    node = lIndex(list, list->length - 1);
    if (node == NULL) return 1;

    node->node = lnCreate(buffer, size);

    list->length++;
    return 0;
}

int lInsert(LIST *list, size_t index, void *buffer, size_t size) {
    LISTNODE *node;
    LISTNODE *nnode;

    if ((list == NULL) || (index > list->length) || (list->node == NULL && list->length == 0 && index != 0)) return 1;
    if (index == 0) {
        lPrepend(list, buffer, size);
        return 0;
    }

    node = lIndex(list, index - 1);
    if (node == NULL) return 1;

    nnode = lnCreate(buffer, size);
    nnode->node = node->node;
    node->node = nnode;

    list->length++;
    return 0;
}

int lDequeue(LIST *list) {
    LISTNODE *node;

    if ((list == NULL) || (list->node == NULL) || (list->length == 0)) return 1;

    node = list->node;
    list->node = node->node;
    lnDelete(&node);

    list->length--;
    return 0;
}

int lPop(LIST *list) {
    LISTNODE *node;

    if ((list == NULL) || (list->node == NULL) || (list->length == 0)) return 1;
    if (list->length == 1) {
        node = list->node;
        list->node = NULL;
        lnDelete(&node);
        list->length--;
        return 0;
    }

    node = lIndex(list, list->length - 2);
    if (node == NULL || node->node == NULL) return 1;

    lnDelete(&node->node);

    list->length--;
    return 0;
}

int lRemove(LIST *list, size_t index) {
    LISTNODE *node;
    LISTNODE *nnode;

    if ((list == NULL) || (list->node == NULL) || (list->length == 0)) return 1;
    if (index == 0) {
        nnode = list->node;
        list->node = nnode->node;
        lnDelete(&nnode);
        list->length--;
        return 0;
    }

    node = lIndex(list, index - 1);
    if (node == NULL || node->node == NULL) return 1;

    nnode = node->node;
    node->node = nnode->node;
    lnDelete(&nnode);

    list->length--;
    return 0;
}

int lnPrepend(LIST *list, LISTNODE *node) {
    if (list == NULL) return 1;

    node->node = list->node;
    list->node = node;

    list->length++;
    return 0;
}

int lnAppend(LIST *list, LISTNODE *node) {
    LISTNODE *nnode;
    
    if (list == NULL) return 1;
    if (list->length == 0) {
        list->node = node;
        list->length++;
        return 0;
    }
    
    nnode = lIndex(list, list->length - 1);
    if (nnode == NULL) return 1;

    node->node = NULL;
    nnode->node = node;

    list->length++;
    return 0;
}

int lnInsert(LIST *list, size_t index, LISTNODE *node) {
    LISTNODE *nnode;

    if ((list == NULL) || (index > list->length) || (list->node == NULL && list->length == 0 && index != 0)) return 1;
    if (index == 0) {
        lnPrepend(list, node);
        return 0;
    }

    nnode = lIndex(list, index);
    if (nnode == NULL) return 1;

    node->node = nnode->node;
    nnode->node = node;

    list->length++;
    return 0;
}

LISTNODE *lnDequeue(LIST *list) {
    LISTNODE *node;

    if ((list == NULL) || (list->node == NULL) || (list->length == 0)) return NULL;

    node = list->node;
    list->node = node->node;

    list->length--;
    return node;
}

LISTNODE *lnPop(LIST *list) {
    LISTNODE *node;

    if ((list == NULL) || (list->node == NULL) || (list->length == 0)) return NULL;
    if (list->length == 1) {
        node = list->node;
        list->node = node->node;
        list->length--;
        return node;
    }

    node = lIndex(list, list->length - 2);
    if (node == NULL) return NULL;

    node->node = NULL;

    list->length--;
    return node;
}

LISTNODE *lnRemove(LIST *list, size_t index) {
    LISTNODE *node;
    LISTNODE *nnode;

    if ((list == NULL) || (list->node == NULL) || (list->length == 0)) return NULL;
    if (index == 1) {
        node = list->node;
        list->length--;
        return node;
    }

    node = lIndex(list, index - 1);
    if (node == NULL) return NULL;

    nnode = node->node;
    node->node = nnode->node;

    list->length--;
    return node;
}
