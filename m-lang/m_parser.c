#ifndef __M_PARSER_C__
#define __M_PARSER_C__

#include <stddef.h>

#include <list.h>

LIST *parser(LIST *lines) {
    LIST *ast;
    LIST *macros;
    M_TOKEN *token;
    M_TOKEN *dummy;

    ast = lCreate();
    macros = lCreate();
    for (size_t i = 0; i < tokens->length; i++) {
        token = lGet(tokens, i);
        switch (token->kind) {
        case TOKEN_DOLLAR:
            dummy = lGet(tokens, i + 1);
            if (dummy == NULL || dummy->kind != TOKEN_LABEL) break;
            
        }
    }

    lDelete(&macros);
    return ast;
}

#endif // __M_PARSER_C__
