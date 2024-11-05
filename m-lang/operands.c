typedef enum DEFAULT_TYPES {
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

    // linked list
    TYPE_LIST,

    // function type
    TYPE_FUNCTION,
} DEFAULT_TYPES;

typedef struct OPERAND_TYPE {
    DEFAULT_TYPES type;
    void *value;
} OPERAND_TYPE;

typedef struct OPERAND_ADD {
    OPERAND_TYPE value1;
    OPERAND_TYPE value2;
} OPERAND_ADD;
