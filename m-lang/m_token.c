#ifndef __M_TOKEN_C__
#define __M_TOKEN_C__

typedef enum M_TOKEN_KIND {
    TOKEN_COMMENT,

    TOKEN_DIGIT,
    TOKEN_LABEL,

    TOKEN_STRING,

    TOKEN_PLUS,
    TOKEN_ASTERISK,
    
    TOKEN_EQUALS,

    TOKEN_AT,
    TOKEN_DOLLAR,

    TOKEN_DOT,
    TOKEN_COMMA,
    TOKEN_COLON,

    TOKEN_PARENTHESE_OPEN,
    TOKEN_PARENTHESE_CLOSE,
    TOKEN_BRACKET_OPEN,
    TOKEN_BRACKET_CLOSE,
    TOKEN_BRACE_OPEN,
    TOKEN_BRACE_CLOSE,
} M_TOKEN_KIND;

typedef struct M_TOKEN {
    M_TOKEN_KIND kind;
    size_t start;
    size_t end;
} M_TOKEN;

typedef struct M_LINE {
    size_t line;
    LIST *tokens;
} M_LINE;

M_TOKEN make_token(M_TOKEN_KIND kind, size_t start, size_t end) {
    return (M_TOKEN){
        .kind = kind,
        .start = start,
        .end = end,
    };
}

#endif // __M_TOKEN_C__
