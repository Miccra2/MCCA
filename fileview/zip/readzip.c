#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

#include "zip.h"

#define USAGE   "Usage: readzip file\n"

void zipFileHeaderInfo(ZIP_FILE_HEADER *file_header) {
    printf("ZIP_FILE_HEADER:\n");
    printf("    signature:              0x%.8X\n", file_header->signature);
    printf("    min. version:           %i\n", file_header->min_version);
    printf("    flags:                  0x%.4X\n", file_header->flags);
    printf("    compression methode:    0x%.4X\n", file_header->compression_methode);
    printf("    last modification time: %i\n", file_header->last_modification_time);
    printf("    last modification date: %i\n", file_header->last_modification_date);
    printf("    CRC32:                  0x%.8X\n", file_header->CRC32);
    printf("    compressed size:        0x%.8X\n", file_header->compressed_size);
    printf("    uncompressed size:      0x%.8X\n", file_header->uncompressed_size);
    printf("    file name length:       0x%.4X\n", file_header->file_name_length);
    printf("    extra field length:     0x%.4X\n", file_header->extra_field_length);
    printf("    file name:              %s\n", file_header->file_name);
    printf("    extra field:            %X\n", file_header->extra_field);
}

bool isZipFileHeader(const char *buffer) {
    ZIP_FILE_HEADER *file_header = (ZIP_FILE_HEADER *)buffer;

    zipFileHeaderInfo(file_header);
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

    fseek(pf, 0, SEEK_END);
    size_t size = ftell(pf);
    char buffer[size];

    fseek(pf, 0, SEEK_SET);
    fread(&buffer, 1, size, pf);

    if (isZipFileHeader(buffer)) {}

    fclose(pf);
    return 0;
}
