#ifndef __TOKEN_C__
#define __TOKEN_C__

typedef enum {
    TOKEN_DIGIT,
    TOKEN_LABEL,

    TOKEN_PLUS,
} TOKEN_KIND;

typedef struct {
    TOKEN_KIND kind;
    char *start;
    char *end;
} TOKEN;

TOKEN make_token(TOKEN_KIND kind, char *start, char *end) {
    return (TOKEN){
        .kind = kind,
        .start = start,
        .end = end,
    };
}

#endif // __TOKEN_C__
