#include <stddef.h>
#include <list.h>

#include "types.h"
#include "tokens.h"

LISTNODE str2int(LISTNODE *token) {
    size_t num = 0;
    for (size_t i = 0; i < token->size; i++) {
        size_t n = num;
        num = num * 10 + token->buffer[i + token->size - 1] - 0x30;
        
        if (n > num) return 0;
    }
    return num;
}

void parser(LIST *tokens) {
    LIST stack = {};
    for (size_t i = 0; i < tokens->length; i++) {
        LISTNODE *token = lIndex(tokens, i);
        switch (*(u32 *)token->buffer) {
        case TOKEN_NUMBER:
            lAppend(&stack, str2int(token));
        }
    }
}
