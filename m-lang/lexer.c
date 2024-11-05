#include <stddef.h>

#include "list.h"
#include "token.c"

#define ISDIGIT(x) (((x) >= '0') && ((x) <= '9'))
#define ISNUMBER(x) ((x) == '.' || ISDIGIT(x))
#define ISLABELSTART(x) (((x) == '_') || ((x) >= 'A' && (x) <=  'Z') || ((x) >= 'a' && (x) <= 'z'))
#define ISLABEL(x) (ISDIGIT(x) || ISLABELSTART(x))

LIST *lexer(char *buffer, size_t size) {
    TOKEN dummy;
    LIST *tokens;
    size_t line;
    size_t cur;

    dummy = (TOKEN){0};
    tokens = lCreate();
    line = 0;
    cur = 0;
    for (size_t i = 0; i < size; i++) {
        switch ( buffer[i] ) {
            case '\n':
                line++;
            case '\r':
            case '\t':
            case ' ':
                cur++;
                break;
            case '+':
                dummy = make_token(TOKEN_PLUS, buffer + cur, buffer + i + 1);
                lAppend(tokens, &dummy, sizeof(dummy));
                cur++;
                break;
            default:
                if ( ISLABELSTART( buffer[i] )) {
                    while (i < size && ISLABEL( buffer[i] )) i++;
                    dummy = make_token(TOKEN_LABEL, buffer + cur, buffer + i);
                    lAppend(tokens, &dummy, sizeof(dummy));
                    cur = i;
                    i--;
                    continue;
                }

                if ( ISDIGIT( buffer[i] )) {
                    while (i < size && ISNUMBER( buffer[i] )) i++;
                    dummy = make_token(TOKEN_DIGIT, buffer + cur, buffer + i);
                    lAppend(tokens, &dummy, sizeof(dummy));
                    cur = i;
                    i--;
                    continue;
                }

                cur++;
                fprintf(stderr, "INFO: invalid token 0x%.2X '%c'!\n", buffer[i], buffer[i]);
                //return NULL;
        }
    }

    return tokens;
}
