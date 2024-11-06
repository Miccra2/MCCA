#ifndef __M_PARSER_C__
#define __M_PARSER_C__

#include <list.h>

LIST *parser(LIST *tokens) {
    LIST *ast;
    LIST *stack;

    ast = lCreate();
    stack = lCreate();
    for (size_t i = 0; i < tokens->length; i++) {
        M_TOKEN *token = lGet(tokens, i);
        switch (token->kind) {
        case TOKEN_NUMBER:
            lAppend(stack, token);
        case TOKEN_PLUS:
            lAppend(ast, token);
        default:
            fprintf(stderr, "ERROR: Invalid token kind '%.4X'!", token->kind);
        }
    }

    lDelete(&stack);
    return ast;
}

#endif // __M_PARSER_C__
