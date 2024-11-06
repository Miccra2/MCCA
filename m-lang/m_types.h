#ifndef __M_TYPES_H__
#define __M_TYPES_H__

typedef enum M_TYPES {
    // undefined types
    TYPE_NONE,
    TYPE_NULL,
    TYPE_VOID,

    // integer types
    TYPE_I8,
    TYPE_I16,
    TYPE_I32,
    TYPE_I64,
    TYPE_U8,
    TYPE_U16,
    TYPE_U32,
    TYPE_U64,
    
    // floating point types
    TYPE_FLOAT,
    TYPE_DOUBLE,

    // character type
    TYPE_CHAR,

    // pointer and array like types
    TYPE_POINTER,
    TYPE_REFERENCE,
    TYPE_ARRAY,
    TYPE_STRING,

    // linked list type
    TYPE_LIST,

    // function type
    TYPE_FUNCTION,

    // variable type
    TYPE_VARIABLE,

    // custom type
    TYPE_CUSTOM,
} M_TYPES;

#endif // __M_TYPES_H__
