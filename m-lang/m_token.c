#ifndef __M_TOKEN_C__
#define __M_TOKEN_C__

typedef enum M_TOKEN_KIND {
    TOKEN_COMMENT,

    TOKEN_DIGIT,
    TOKEN_LABEL,

    TOKEN_STRING,

    TOKEN_PLUS,
} M_TOKEN_KIND;

typedef struct M_TOKEN {
    M_TOKEN_KIND kind;
    char *start;
    char *end;
} M_TOKEN;

M_TOKEN make_token(M_TOKEN_KIND kind, char *start, char *end) {
    return (M_TOKEN){
        .kind = kind,
        .start = start,
        .end = end,
    };
}

#endif // __M_TOKEN_C__
