#include <stdio.h>

#include "elf.h"

#define USAGE   "Usage: readelf file\n"

void load(void *dat, void *buf, u64 size) {
    for (u64 i = 0; i < size; i++) {
        ((char *)buf)[i] = ((char *)dat)[i];
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("ERROR: To few input arguments given, please provide more input arguments!\n");
        printf(USAGE);
        return 1;
    }

    FILE *pf = fopen(argv[1], "rb");
    if (pf == NULL) {
        printf("ERROR: Invalid file '%s' given, please provide a valid file!\n");
        printf(USAGE);
        return 1;
    }


    return 0;
}
