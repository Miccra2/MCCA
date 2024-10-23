#include <stdio.h>
#include <stdint.h>

#define USAGE   "Usage: dump file [offset] [length]\n"
#define szU64_C sizeof(uint64_t) / sizeof(char)

uint64_t str2u64(const char *str) {
    char *strptr = (char *)str;
    uint64_t num = 0;
    
    while (*strptr >= '0' && *strptr <= '9')
        strptr++;

    for (uint64_t i = 1; str + i < strptr; i++) {}
}

char *dump() {}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("ERROR: To few input arguments given, please provide more input arguments!\n");
        printf(USAGE);
        return 1;
    }

    FILE *pf = fopen(argv[1], "rb");
    if (pf == NULL) {
        printf("ERROR: Invalid file '%s' given, please provide a valid file!\n", argv[1]);
        printf(USAGE);
        return 1;
    }

    fseek(pf, 0, SEEK_END);
    uint64_t size = ftell(pf);
    char buffer[size + szU64_C];
    char *data = buffer + szU64_C;
    *(uint64_t *)buffer = size;
    
    fseek(pf, 0, SEEK_SET);
    fread(&data, size, pf);

    uint64_t offset = 0;
    uint64_t length = 0;
    if (argc > 2)
        offset = str2u64(argv[2]);
    if (argc > 3)
        length = str2u64(argv[3]);
    if (offset + length > size)
        length = size - offset;

    printf(dump());

    return 0;
}
