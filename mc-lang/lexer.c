#include <stddef.h>
#include <list.h>
#include <reader.h>

#include "types.h"
#include "tokens.h"

#define ISDIGIT(x) x >= '0' && x <= '9'
#define ISLABELSTART(x) x == '_' || (x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z')
#define ISLABEL(x) ISLABELSTART(x) || ISDIGIT(x)

void lexer(READER *reader, LIST *tokens) {
    size_t line = 0;
    u32 token = TOKEN_NONE;
    while (reader->cur - reader->buf < reader->size) {
        switch (*reader->cur) {
        case '\n':
            line++;
        case '\r':
        case '\t':
        case ' ':
            reader->cur++;
            rCut(reader, NULL);
            break;

        case '+':
            token = TOKEN_PLUS;
            lAppend(tokens, lnCreate(&token, sizeof(token)));
            reader->cur++;
            rCut(reader, NULL);
            break;

        default:
            if (ISLABELSTART(*reader->cur)) {
                while (reader->cur - reader->buf < reader->size && ISLABEL(*reader->cur)) reader->cur++;
                
                token = TOKEN_LABEL;
                size_t label_token_size = sizeof(token) + sizeof(u32) + reader->cur - reader->ptr;
                char label_token[label_token_size];
                
                *(u32 *)label_token = token;
                *((u32 *)label_token + 1) = reader->cur - reader->ptr;
                rCut(reader, label_token + sizeof(token) + sizeof(u32));
                
                lAppend(tokens, lnCreate(label_token, label_token_size));
                continue;
            }

            if (ISDIGIT(*reader->cur)) {
                while (reader->cur - reader->buf < reader->size && ISDIGIT(*reader->cur)) reader->cur++;
                
                token = TOKEN_NUMBER;
                size_t number_token_size = sizeof(token) + sizeof(u32) + reader->cur - reader->ptr;
                char number_token[number_token_size];
                
                *(u32 *)number_token = token;
                *((u32 *)number_token + 1) = reader->cur - reader->ptr;
                rCut(reader, number_token + sizeof(token) + sizeof(u32));
                
                lAppend(tokens, lnCreate(number_token, number_token_size));
                continue;
            }
        }
    } 
}
