#include "reader.h"

READER *rCreate(void *buffer, size_t size) {
    READER *reader = malloc(sizeof(READER) + size);
    
    reader->size = size;
    reader->ptr = 0;
    reader->cur = 0

    for (size_t i = 0; i < size; i++) {
        reader->buf[i] = ((char *)buffer)[i];
    }

    return reader;
}

void rCut(char *buffer, READER *reader) {
    if (buffer == NULL) {
        reader->ptr = reader->cur;
        return;
    }

    for (size_t i = 0; i < reader->cur - reader->ptr; i++) {
        buffer[i] = reader->buf[i];
    }

    reader->ptr = reader->cur;
}

size_t rLen(READER *reader) {
    return reader->cur - reader->ptr;
}
