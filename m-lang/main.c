#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "list.h"
#include "m_token.c"
#include "m_types.h"
#include "m_operands.c"
#include "m_lexer.c"
//#include "m_parser.c"

#define USAGE   "Usage: mcc <file>\n"

void printTokens(LIST *tokens) {
    printf("\n");
    for (size_t i = 0; i < tokens->length; i++) {
        M_TOKEN *token = (M_TOKEN *)lIndex(tokens, i)->buffer;
        char *pcur = token->start;
        printf("%i: '", token->kind);
        while (pcur < token->end) {
            printf("%c", *pcur++);
        }
        printf("'\n");
    }
}

int main(int argc, char *argv[]) {
    FILE *pFile;
    size_t size;
    char *buffer;
    LIST *tokens;
    LIST *ast;

    if (argc < 2) {
        fprintf(stderr, "ERROR: To few input arguments given, please provide more input arguments!\n");
        fprintf(stderr, USAGE);
        return 1;
    }

    pFile = fopen(argv[1], "rb");
    if (pFile == NULL) {
        fprintf(stderr, "ERROR: Invalid input file given, please provide a valide input file!\n");
        fprintf(stderr, USAGE);
        return 1;
    }

    fseek(pFile, 0, SEEK_END);
    size = ftell(pFile);
    buffer = malloc(size);
    
    fseek(pFile, 0, SEEK_SET);
    fread(buffer, 1, size, pFile);

    tokens = lexer(buffer, size);
    if (tokens == NULL) goto FINISH;

    //ast = parser(tokens);
    //if (ast == NULL) goto FINISH;

    printTokens(tokens);
    //printf("tokens->length: %i\n", tokens->length);

FINISH:
    //if (ast)    lDelete(&ast);
    if (tokens) lDelete(&tokens);
    if (pFile)  fclose(pFile);
    return 0;
}
