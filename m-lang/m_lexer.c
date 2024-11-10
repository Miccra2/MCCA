#ifndef __M_LEXER_C__
#define __M_LEXER_C__

#include <stddef.h>

#include "list.h"
#include "m_token.c"

#define ISDIGIT(x) (((x) >= '0') && ((x) <= '9'))
#define ISNUMBER(x) ((x) == '.' || ISDIGIT(x))
#define ISLABELSTART(x) (((x) == '_') || ((x) >= 'A' && (x) <=  'Z') || ((x) >= 'a' && (x) <= 'z'))
#define ISLABEL(x) (ISDIGIT(x) || ISLABELSTART(x))

LIST *lexer(char *buffer, size_t size) {
    M_TOKEN dummy;
    M_LINE line;
    LIST *tokens;
    LIST *lines;
    size_t l;
    size_t cur;

    dummy = (M_TOKEN){0};
    tokens = lCreate();
    lines = lCreate();
    l = 0;
    cur = 0;
    for (size_t i = 0; i < size; i++) {
        switch ( buffer[i] ) {
        case '\n':
            l++;
            line = (M_LINE){
                .line = l,
                .tokens = tokens,
            };
            lAppend(lines, &line, sizeof(line));
            tokens = lCreate();
        case '\r':
        case '\t':
        case ' ':
            cur = i;
            break;
        case '/':
            cur = i;
            if (i + 1 < size && buffer[i++] == '/') {
                while (i < size && buffer[i] != '\n') i++;
                dummy = make_token(TOKEN_COMMENT, cur, i - 1);
                lAppend(tokens, &dummy, sizeof(dummy));
            }
            break;
        case '"':
            i++;
            cur = i;
            while (i < size && buffer[i] != '"') {
                if (i < size && buffer[i] == '\\')
                    i++;
                i++;
            }
            dummy = make_token(TOKEN_STRING, cur, i);
            lAppend(tokens, &dummy, sizeof(dummy));
            break;
        case '+':
            cur = i;
            dummy = make_token(TOKEN_PLUS, cur, i + 1);
            lAppend(tokens, &dummy, sizeof(dummy));
            break;
        case '*':
            cur = i;
            dummy = make_token(TOKEN_ASTERISK, cur, i + 1);
            lAppend(tokens, &dummy, sizeof(dummy));
            break;
        case '=':
            cur = i;
            dummy = make_token(TOKEN_EQUALS, cur, i + 1);
            lAppend(tokens, &dummy, sizeof(dummy));
            break;
        case '@':
            cur = i;
            dummy = make_token(TOKEN_AT, cur, i + 1);
            lAppend(tokens, &dummy, sizeof(dummy));
            break;
        case '$':
            cur = i;
            dummy = make_token(TOKEN_DOLLAR, cur, i + 1);
            lAppend(tokens, &dummy, sizeof(dummy));
            break;
        case '.':
            cur = i;
            dummy = make_token(TOKEN_DOT, cur, i + 1);
            lAppend(tokens, &dummy, sizeof(dummy));
            break;
        case ',':
            cur = i;
            dummy = make_token(TOKEN_COMMA, cur, i + 1);
            lAppend(tokens, &dummy, sizeof(dummy));
            break;
        case ';':
            cur = i;
            dummy = make_token(TOKEN_COLON, cur, i + 1);
            lAppend(tokens, &dummy, sizeof(dummy));
            break;
        case '(':
            cur = i;
            dummy = make_token(TOKEN_PARENTHESE_OPEN, cur, i + 1);
            lAppend(tokens, &dummy, sizeof(dummy));
            break;
        case ')':
            cur = i;
            dummy = make_token(TOKEN_PARENTHESE_CLOSE, cur, i + 1);
            lAppend(tokens, &dummy, sizeof(dummy));
            break;
        case '[':
            cur = i;
            dummy = make_token(TOKEN_BRACKET_OPEN, cur, i + 1);
            lAppend(tokens, &dummy, sizeof(dummy));
            break;
        case ']':
            cur = i;
            dummy = make_token(TOKEN_BRACKET_CLOSE, cur, i + 1);
            lAppend(tokens, &dummy, sizeof(dummy));
            break;
        case '{':
            cur = i;
            dummy = make_token(TOKEN_BRACE_OPEN, cur, i + 1);
            lAppend(tokens, &dummy, sizeof(dummy));
            break;
        case '}':
            cur = i;
            dummy = make_token(TOKEN_BRACE_CLOSE, cur, i + 1);
            lAppend(tokens, &dummy, sizeof(dummy));
            break;
        default:
            if ( ISLABELSTART( buffer[i] )) {
                cur = i;
                while (i < size && ISLABEL( buffer[i] )) i++;
                dummy = make_token(TOKEN_LABEL, cur, i);
                lAppend(tokens, &dummy, sizeof(dummy));
                i--;
                continue;
            }

            if ( ISDIGIT( buffer[i] )) {
                cur = i;
                while (i < size && ISNUMBER( buffer[i] )) i++;
                dummy = make_token(TOKEN_DIGIT, cur, i);
                lAppend(tokens, &dummy, sizeof(dummy));
                i--;
                continue;
            }

            cur = i;
            fprintf(stderr, "INFO: invalid token 0x%.2X '%c'!\n", buffer[i], buffer[i]);
            //return NULL;
        }
    }

    if (tokens != NULL && tokens->length > 0) {
        line = (M_LINE){
            .line = l,
            .tokens = tokens,
        };
    }
    else {
        lDelete(&tokens);
    }

    return lines;
}

#endif // __M_LEXER_C__
