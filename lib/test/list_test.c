#include <stdio.h>

#include <list.h>

int main() {
    printf("LIST: %i, LISTNODE: %i, size_t: %i\n", sizeof(LIST), sizeof(LIST), sizeof(size_t));

    size_t t0 = 0x1;
    size_t t1 = 0x2;
    size_t t2 = 0x4;
    size_t t3 = 0x8;
    size_t t4 = 0x10;
    size_t t5 = 0x20;
    size_t t6 = 0x40;
    size_t t7 = 0x80;

    PLIST list = lCreate();

    lIndex(list, 0);
    lIndex(list, 1);

    printf("prepend:\n");
    lPrepend(list, 8, &t0);
    printf("  t0:           0x%.2X\n", *(size_t *)lGet(list, 0));
    lDequeue(list);
    printf("  list->node:   0x%.16X\n", list->node);
    printf("  list->length: %i\n\n", list->length);

    printf("append:\n");
    lAppend(list, 8, &t1);
    printf("  t1:           0x%.2X\n", *(size_t *)lGet(list, 0));
    lPop(list);
    printf("  list->node:   0x%.16X\n", list->node);
    printf("  list->length: %i\n\n", list->length);

    printf("insert_0:\n");
    lInsert(list, 0, 8, &t2);
    printf("  t2:           0x%.2X\n", *(size_t *)lGet(list, 0));
    lRemove(list, 0);
    printf("  list->node:   0x%.16X\n", list->node);
    printf("  list->length: %i\n\n", list->length);

    printf("insert_1:\n");
    lInsert(list, 1, 8, &t3);
    printf("  t3:           0x%.2X\n", *(size_t *)lGet(list, 1));
    lRemove(list, 1);
    printf("  list->node:   0x%.16X\n", list->node);
    printf("  list->length: %i\n\n", list->length);

    printf("insert_2:\n");
    lInsert(list, 0, 8, &t4);
    lInsert(list, 1, 8, &t5);
    printf("  t4:           0x%.2X\n", *(size_t *)lGet(list, 0));
    printf("  t5:           0x%.2X\n", *(size_t *)lGet(list, 1));
    lRemove(list, 1);
    lRemove(list, 0);
    printf("  list->node:   0x%.16X\n", list->node);
    printf("  list->length: %i\n\n", list->length);

    lDelete(&list);
    return 0;
}
