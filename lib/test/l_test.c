#include <stdio.h>
#include <stddef.h>
#include <list.h>

void lInfo(LIST *list) {
    printf("list.length: %i\n", list->length);

    for (size_t i = 0; i < list->length; i++) {
        printf("list[%i]: %i\n", i, *(int *)(lIndex(list, i)->buffer));
    }

    printf("\n");
}

int main(int argc, char *argv[]) {
    int a = 69;
    int b = 420;
    int c = 3001;
    
    LIST list = {0};

    printf("%i\n", sizeof(a));
    
    lPrepend(&list, lnCreate(&a, sizeof(a)));
    lAppend(&list, lnCreate(&b, sizeof(b)));

    lInfo(&list);

    lInsert(&list, lnCreate(&c, sizeof(c)), 1);

    lInfo(&list);

    lRemove(&list, 1);

    lInfo(&list);

    lPop(&list);
    lDequeue(&list);

    lInfo(&list);

    lAppend(&list, lnCreate(&a, sizeof(a)));
    
    lInfo(&list);

    lDelete(&list);

    return 0;
}
