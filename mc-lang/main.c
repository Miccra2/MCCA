#include <stdio.h>
#include <stdint.h>

#include <list.h>
#include <reader.h>

#include "lexer.c"
#include "parser.c"
#include "interpreter.c"

#define USAGE   "Usage: mcc <file>\n"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("ERROR: To few input arguments given, please provide more input arguments!\n");
        printf(USAGE);
        return 1;
    }
    
    FILE *pf = fopen(argv[1], "rb");
    if (pf == NULL) {
        printf("ERROR: Invalid input file '%s' given, please provide a valid input file!\n", argv[1]);
        printf(USAGE);
        return 1;
    }

    fseek(pf, 0, SEEK_END);
    size_t size = ftell(dpf);
    char buffer[size];
    READER *reader = rCreate(buffer, size);

    fseek(pf, 0, SEEK_SET);
    fread(&reader->buf, 1, size, pf);

    LIST tokens = {};
    
    lexer(reader, &tokens);
    parser(&tokens);
    interpreter(&tokens);
    
    char *data;
    printf("TOKEN_NUMBER: %i\n", TOKEN_NUMBER);
    
    data = lIndex(&tokens, 0)->buffer;
    printf("tokens[0]: %i %i '%s'\n", ((uint32_t *)data)[0], ((uint32_t *)data)[1], data + sizeof(uint32_t) * 2);
    
    data = lIndex(&tokens, 2)->buffer;
    printf("tokens[2]: %i %i '%s'\n", ((uint32_t *)data)[0], ((uint32_t *)data)[1], data + sizeof(uint32_t) * 2);
    
    data = lIndex(&tokens, 1)->buffer;
    printf("TOKEN_PLUS: %i\n", TOKEN_PLUS);
    printf("tokens[1]: %i\n", *(uint32_t *)data);
    
    lDelete(&tokens);
    free(reader);
    fclose(pf);
    return 0;
}
