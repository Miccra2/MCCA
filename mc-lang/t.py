from dataclasses import dataclass

class LListNode:
    pass

@dataclass
class LListNode:
    node: LListNode | None = None
    size: int = 0
    buffer: bytes = b""

@dataclass
class LList:
    length: int = 0
    node: LListNode | None = None

"""
void lDelete(LIST *list) {
    if (list->length == 0 || list->node == NULL) return;
    if (list->length == 1) {
        free(list->node);
        return;
    }

    size_t i = 0;
    LISTNODE *node = list->node;
    LISTNODE *nnode = node->node;
    while (node != NULL) {
        printf("i: %i\n", i++);
        printf("node:  0x%.16X, node->node:  0x%.16X, node->size:  %i, node->buffer: 0x%.16X\n", node, node->node, node->size, node->buffer);
        printf("nndoe: 0x%.16X, nnode->node: 0x%.16X, nndoe->size: %i, nnode->buffer: 0x%.16X\n\n", nnode, nnode->node, nnode->size, nnode->buffer);
        free(node);
        node = nnode;
        nnode = nnode->node;
    }

    free(node);

    list->node = NULL;
}
"""
def lDelete(llist: LList) -> None:
    if (llist.length == 0 or llist.length == None): return
    if (llist.length == 1):
        del llist.node
        return

    i: int = 0
    node: LListNode = llist.node
    nnode: LListNode = node.node
    while nnode != None:
        del node
        node = nnode
        nnode = nnode.node
        print(i)
        i += 1

    del node
    llist.node = None

"""
void lAppend(LIST *list, void *buffer, size_t size) {
    if (list->length == 0 || list->node == NULL) {
        if (list->node != NULL) free(list->node);
        list->length++;
        list->node = lnCreate(buffer, size);
        return;
    }

    LISTNODE *node = list->node;
    size_t i = 1;
    while (i < list->length && node->node != NULL) {
        node = node->node;
        i++;
    }
    
    list->length++;
    if (node->node) free(node->node);
    node->node = lnCreate(buffer, size);
}
"""
def lAppend(llist: LList, buffer: bytes, size: int) -> None:
    if llist.length == 0 or llist.node == None:
        if llist.node != None: del llist.node
        llist.length += 1
        llist.node = lnCreate(buffer, size)
        return

    node: LListNode = llist.node
    i: int = 1
    while i < llist.length and node.node != None:
        node = node.node
        i += 1

    llist.length += 1
    if node.node: del node.node
    node.node = lnCreate(buffer, size)

"""
LISTNODE *lnCreate(void *buffer, size_t size) {
    LISTNODE *node = malloc(sizeof(LISTNODE) + size);
    node->node = NULL;
    node->size = size;
    
    for (size_t i = 0; i < size; i++) {
        node->buffer[i] = ((char *)buffer)[i];
    }

    return node;
}
"""
def lnCreate(buffer: bytes, size: int) -> LListNode:
    return LListNode(None, size, buffer)

def lCreate() -> LList:
    return LList(0, None)

l = lCreate()
for i in range(100):
    lAppend(l, "A%.2X" % i, 3)

lDelete(l)
