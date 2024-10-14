#include <stdio.h>
#include <stddef.h>

#define USAGE   "Usage: dump <file> [offset] [length]\n" \
                "    offset: offset into file to start from\n" \
                "    length: size of shown area\n"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("[Error] InputArguments: To few arguments given, please provide more arguments!\n");
        printf(USAGE);
        return 1;
    }

    FILE *pf = fopen(argv[1], "rb");
    if (pf == NULL) {
        printf("[Error] InputArguments: Invalid file '%s' given, please provide a valid file!\n", argv[1]);
        printf(USAGE);
        return 1;
    }

    size_t offset = 0;
    size_t length = 0;
    if (argc > 2) {
        offset = str2u64();
    }

    fclose(pf);
    return 0;
}
