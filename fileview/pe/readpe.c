#include <stdio.h>

#include "pe.h"
#include "peinfo.c"

#define USAGE   "Usage: readpe <file>\n"

void parsepe(FILE *pf) {
    IMAGE_DOS_HEADER DosHdr;
    fread(&DosHdr, 1, sizeof(DosHdr), pf);

    if (DosHdr.e_magic != IMAGE_DOS_SIGNATURE) {
        return;
    }

    printf("IMAGE_DOS_HEADER:\n");
    printf("  e_magic: %.4X\n", DosHdr.e_magic);
    printf("  e_lfanew: %.8X\n", DosHdr.e_lfanew);

    IMAGE_NT_HEADERS32 ntHdrs;
    fseek(pf, DosHdr.e_lfanew, SEEK_SET);
    fread(&ntHdrs, 1, sizeof(IMAGE_NT_HEADERS32), pf);

    OptHdr32Info(&ntHdrs.OptionalHeader);
    //printf("nt32:  %i\n", sizeof(IMAGE_NT_HEADERS32));
    //printf("opt32: %i\n", sizeof(IMAGE_OPTIONAL_HEADER32));
    //printf("nt64:  %i\n", sizeof(IMAGE_NT_HEADERS64));
    //printf("opt64: %i\n", sizeof(IMAGE_OPTIONAL_HEADER64));
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("[Error] InputArguments: To few arguments given,"
                " please provide more arguments!\n");
        printf(USAGE);
        return 1;
    }

    FILE *pf = fopen(argv[1], "rb");
    if (pf == NULL) {
        printf("[Error] InputArguments: Invalid file '%s' given, please"
                " provide a valid file!\n", argv[1]);
        printf(USAGE);
        return 1;
    }

    parsepe(pf);

    fclose(pf);
    return 0;
}
