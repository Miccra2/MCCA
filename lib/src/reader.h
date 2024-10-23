#ifndef __READER_H__
#define __READER_H__

#include <stdlib.h>
#include <stddef.h>

typedef struct {
    size_t ptr;
    size_t cur;
    size_t size;
    char buf[];
} READER;

READER *rCreate(void *buffer, size_t size);
void rCut(READER *reader, char *buffer);
size_t rLen(READER *reader);

#endif // __READER_H__
