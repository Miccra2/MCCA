#ifndef __M_LEXER_C__
#define __M_LEXER_C__

#include <stddef.h>

#include "list.h"
#include "m_token.c"

#define ISDIGIT(x) (((x) >= '0') && ((x) <= '9'))
#define ISNUMBER(x) ((x) == '.' || ISDIGIT(x))
#define ISLABELSTART(x) (((x) == '_') || ((x) >= 'A' && (x) <=  'Z') || ((x) >= 'a' && (x) <= 'z'))
#define ISLABEL(x) (ISDIGIT(x) || ISLABELSTART(x))

LIST *lexer(char *buffer, size_t size) {
    M_TOKEN dummy;
    LIST *tokens;
    size_t line;
    size_t cur;

    dummy = (M_TOKEN){0};
    tokens = lCreate();
    line = 0;
    cur = 0;
    for (size_t i = 0; i < size; i++) {
        printf("cur: %i, i: %i\n", cur, i);
        switch ( buffer[i] ) {
        case '\n':
            line++;
        case '\r':
        case '\t':
        case ' ':
            cur = i;
            break;
        case '/':
            if (i + 1 < size && buffer[i++] == '/') {
                while (i < size && buffer[i] != '\n') i++;
                dummy = make_token(TOKEN_COMMENT, buffer + cur, buffer + i - 1);
                cur = i;
            }
            break;
        case '"':
            i++;
            cur = i;
            while (i < size && buffer[i] != '"') {
                if (i < size && buffer[i] == '\\')
                    i++;
                i++;
            }
            dummy = make_token(TOKEN_STRING, buffer + cur, buffer + i);
            lAppend(tokens, &dummy, sizeof(dummy));
            break;
        case '+':
            cur = i;
            dummy = make_token(TOKEN_PLUS, buffer + cur, buffer + i + 1);
            lAppend(tokens, &dummy, sizeof(dummy));
            break;
        default:
            if ( ISLABELSTART( buffer[i] )) {
                cur = i;
                while (i < size && ISLABEL( buffer[i] )) i++;
                dummy = make_token(TOKEN_LABEL, buffer + cur, buffer + i);
                lAppend(tokens, &dummy, sizeof(dummy));
                i--;
                continue;
            }

            if ( ISDIGIT( buffer[i] )) {
                cur = i;
                while (i < size && ISNUMBER( buffer[i] )) i++;
                dummy = make_token(TOKEN_DIGIT, buffer + cur, buffer + i);
                lAppend(tokens, &dummy, sizeof(dummy));
                i--;
                continue;
            }

            cur = i;
            fprintf(stderr, "INFO: invalid token 0x%.2X '%c'!\n", buffer[i], buffer[i]);
            //return NULL;
        }
    }

    return tokens;
}

#endif // __M_LEXER_C__
