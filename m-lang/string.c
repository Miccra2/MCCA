#include <stddef.h>

#include "range.c"

typedef struct STRING {
    size_t size;
    char *str;
} STRING;

void cut(char *buffer, char *target, RANGE _range) {
    for (size_t i = _range.start; i < _range.stop; i +=  _range.step) {
        target[i] =  buffer[i];
    }
}
