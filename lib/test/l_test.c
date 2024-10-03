#include <stdio.h>

#include <list.h>

int main() {
    size_t a = 69;
    size_t b = 420;
    size_t c = 3001;

    PLIST list = lCreate();

    lAppend(list, 8, &a);
    lAppend(list, 8, &b);
    lAppend(list, 8, &c);

    printf("0: %i\n", *(size_t *)lGet(list, 0));
    printf("1: %i\n", *(size_t *)lGet(list, 1));
    printf("2: %i\n", *(size_t *)lGet(list, 2));

    lDelete(&list);
    return 0;
}
