#include "list.h"

PLIST lCreate() {
    PLIST list = malloc(sizeof(LIST));
    list->length = 0;
    list->node = NULL;
    
    return list;
}

PLISTNODE lCreateNode(size_t size, void *buffer) {
    PLISTNODE node = malloc(sizeof(LISTNODE) + size);
    node->node = NULL;
    node->size = size;
    
    for (size_t i = 0; i < size; i++) {
        node->buffer[i] = ((char *)buffer)[i];
    }
    
    return node;
}

size_t lDelete(PLIST *list) {
    PLISTNODE dnode = (*list)->node;
    free(*list);
    *list = NULL;

    while (dnode != NULL) {
        PLISTNODE node = dnode->node;
        free(dnode);
        dnode = node;
    }

    return 0;
}

size_t lDeleteNode(PLISTNODE *node) {
    free(*node);
    *node = NULL;
    return 0;
}

PLISTNODE lIndex(PLIST list, size_t index) {
    PLISTNODE node = list->node;
    
    if (index == 0)
        return node;
    if (node == NULL)
        return NULL;
    
    size_t i = 0;
    while (i < list->length && i < index && node->node != NULL) {
        node = node->node;
        i++;
    }
    
    if (i == index)
        return node;
    
    return NULL;
}

char *lGet(PLIST list, size_t index) {
    PLISTNODE node = lIndex(list, index);
    return node->buffer;
}

size_t lPrepend(PLIST list, size_t size, void *buffer) {
    PLISTNODE node = lCreateNode(size, buffer);
    node->node = list->node;
    list->node = node;
    list->length++;
    
    return 0;
}

size_t lAppend(PLIST list, size_t size, void *buffer) {
    if (list->node == NULL) {
        list->node = lCreateNode(size, buffer);
        list->length++;
        return 0;
    }
    
    PLISTNODE node = lIndex(list, list->length - 1);
    node->node = lCreateNode(size, buffer);
    list->length++;
    
    return 0;
}

size_t lInsert(PLIST list, size_t index, size_t size, void *buffer) {
    if (index == 0) {
        list->node = lCreateNode(size, buffer);
        list->length++;
        return 0;
    }
    
    PLISTNODE node = lIndex(list, index - 1);
    node->node = lCreateNode(size, buffer);
    list->length++;
    
    return 0;
}

PLISTNODE lDequeue(PLIST list) {
    if (list->length < 1)
        return NULL;
    
    if (list->node == NULL)
        return NULL;

    PLISTNODE node = list->node;
    list->node = node->node;
    list->length--;

    return node;
}

PLISTNODE lPop(PLIST list) {
    if (list->length < 1)
        return NULL;
    
    if (list->length == 1) {
        list->length--;
        return list->node;
    }
    
    PLISTNODE node = lIndex(list, list->length - 2);
    PLISTNODE dnode = node->node;
    node->node = NULL;
    list->length--;

    return dnode;
}

PLISTNODE lRemove(PLIST list, size_t index) {
    if (list->length < 1)
        return NULL;

    if (list->length == 1) {
        list->length--;
        return list->node;
    }

    PLISTNODE node = lIndex(list, index - 1);
    PLISTNODE dnode = node->node;

    if (dnode == NULL)
        return NULL;

    node->node = dnode->node;
    list->length--;
    
    return dnode;
}
