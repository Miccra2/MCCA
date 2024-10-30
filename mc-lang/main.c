#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define USAGE   "Usage: mcc file\n"

#define ISDIGIT(x) (x >= '0' && x <= '9')
#define ISLABELSTART(x) (x == '_' || (x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z'))
#define ISLABEL(x) (ISLABELSTART(x) || ISDIGIT(x))

typedef struct {
    size_t type;
    size_t size;
    char buffer[];
} TOKEN;

enum {
    TOKEN_NONE,
    TOKEN_LABEL,
    TOKEN_NUMBER,
};

typedef struct LISTNODE LISTNODE;
struct LISTNODE {
    LISTNODE *node;
    size_t size;
    char buffer[];
};

typedef struct LIST {
    size_t length;
    LISTNODE *node;
} LIST;

LIST lCreate() {
    return (LIST){.length = 0, .node = NULL};
}

void lDelete(LIST *list) {
    if (list->length == 0 || list->node == NULL) return;
    if (list->length == 1) {
        free(list->node);
        list->node = NULL;
        return;
    }

    size_t i = 1;
    LISTNODE *node = list->node;
    LISTNODE *nnode = node->node;
    while (i < list->length, nnode != NULL) {
        TOKEN *token = (void *)node->buffer;
        //printf("[lDelete] %i, 0x%.16X, 0x%.16X, %i, %i, %i, '%s'\n", i++, node, nnode, node->size, token->type, token->size, token->buffer);
        free(node);
        node = nnode;
        nnode = nnode->node;
    }

    free(node);

    list->node = NULL;
}

LISTNODE *lnCreate(void *buffer, size_t size) {
    LISTNODE *node = malloc(sizeof(LISTNODE) + size);
    node->node = NULL;
    node->size = size;
   
    for (size_t i = 0; i < size; i++) {
        node->buffer[i] = ((char *)buffer)[i];
    }

    return node;
}

void lnDelete(LISTNODE **node) {
    free(*node);
    *node = NULL;
}

void lAppend(LIST *list, void *buffer, size_t size) {
    if (list->length == 0 || list->node == NULL) {
        if (list->node != NULL) free(list->node);
        list->length++;
        list->node = lnCreate(buffer, size);
        return;
    }

    LISTNODE *node = list->node;
    size_t i = 1;
    while (i < list->length && node->node != NULL) {
        node = node->node;
        i++;
    }
    
    list->length++;
    if (node->node) free(node->node);
    node->node = lnCreate(buffer, size);
}

LISTNODE *lIndex(LIST *list, size_t index) {
    if (list->node == NULL || list->length == 0) return NULL;
    if (index == 1) {
        return list->node;
    }

    LISTNODE *node = list->node;
    size_t i = 1;
    while (i < index && node->node != NULL) {
        node = node->node;
        i++;
    }

    if (i < index) return NULL;

    return node;
}

void cut(const char *text, void *buffer, char **cursor, char **pointer) {
    if (buffer == NULL) {
        *pointer = *cursor;
        return;
    }

    size_t i = 0;
    while (*pointer < *cursor) {
        //printf("[cut] buffer: 0x%.16X, cur: %i, ptr: %i, cur-ptr: %i, i: %i, s: '%s'\n", buffer, *cursor, *pointer, *cursor-*pointer, i, text+*pointer);
        //printf("===========================================================================================\n");
        *((char *)buffer + i++) = (**pointer)++;
    }
}

void lexer(const char *text, size_t size, LIST *tokens) {
    size_t buffer_size = 0;
    size_t line = 0;
    char *ptr = (char *)text;
    TOKEN *token = NULL;
    
    for (char *cur = (char *)text; cur - text <= size; cur++) {
        switch (*cur) {
        case '\n':
            line++;
        case '\r':
        case '\t':
        case ' ':
            cur++;
            cut(text, NULL, &cur, &ptr);
            break;
        default:
            if (ISLABELSTART(*cur)) {
                while (cur - text <= size && ISLABEL(*cur)) cur++;
                buffer_size = cur - ptr + 1;
                printf("[lexer] cur: 0x%.16X, ptr: 0x%.16X, size: %i\n", cur , ptr, buffer_size);
                token = malloc(sizeof(TOKEN) + buffer_size);
                token->type = TOKEN_LABEL;
                token->size = 0;
                token->buffer[buffer_size] = 0;
                cut(text, token->buffer, &cur, &ptr);
                lAppend(tokens, token, sizeof(TOKEN) + buffer_size);
                free(token);
                token = NULL;
                continue;
            }

            /*if (ISDIGIT(*cur)) {
                while (cur < size && ISDIGIT(*cur)) cur++;
                buffer_size = cur - ptr;
                token = malloc(sizeof(TOKEN) + 8);
                token->type = TOKEN_NUMBER;
                token->size = 8;
                str2num(tokens, token->buffer);
                continue;
            }*/

            cur++;
        }
    }

    if (token) free(token);
}

int main(int argc, char *argv[]) {
    FILE *pfile = NULL;
    size_t size = 0;

    if (argc < 2) {
        printf("ERROR: To few input arguments given, please provide more input arguments!\n");
        printf(USAGE);
        return 1;
    }

    pfile = fopen(argv[1], "rb");
    if (pfile == NULL) {
        printf("ERROR: Invalid input file given, please provide a valid input file!\n");
        printf(USAGE);
        return 1;
    }

    fseek(pfile, 0, SEEK_END);
    size = ftell(pfile);
    char buffer[size];

    fseek(pfile, 0, SEEK_SET);
    fread(&buffer, size, 1, pfile);

    /* ===== LEXER ===== */

    LIST tokens = lCreate();
    lexer(buffer, size, &tokens);

    printf("%i\n", tokens.length);

    lDelete(&tokens);
    if (pfile) fclose(pfile);
    return 0;
}
