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

void printTokens(LIST *lines, char *buffer) {
    printf("\n");
    for (size_t i = 0; i < lines->length; i++) {
        M_LINE *line = lGet(lines, i);
        
        for (size_t j = 0; j < line->tokens->length; j++) {
            M_TOKEN *token = lGet(line->tokens, j);
            size_t cur = token->start;
            
            printf("%li: kind=%i \"", line->line, token->kind);
            while (cur < token->end)
                printf("%c", buffer[cur++]);
            
            printf("\"\n");
        }
    }
}

int main(int argc, char *argv[]) {
    FILE *pFile;
    size_t size;
    char *buffer;
    LIST *lines;
    //LIST *ast;

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

    lines = lexer(buffer, size);
    if (lines == NULL) goto FINISH;

    //ast = parser(tokens);
    //if (ast == NULL) goto FINISH;

    printTokens(lines, buffer);
    printf("len(buffer)=%li, len(lines)=%li\n", size, lines->length);

FINISH:
    //if (ast)    lDelete(&ast);
    for (size_t i = 0; i < lines->length; i++) {
        M_LINE *line = lGet(lines, i);
        lDelete(&line->tokens);
    }
    if (lines) lDelete(&lines);
    if (buffer) free(buffer);
    if (pFile) fclose(pFile);
    return 0;
}
