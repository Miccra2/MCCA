#include <types.h>

typedef struct {
    u32 signature;
    u16 min_version;
    u16 flags;
    u16 compression_methode;
    u16 last_modification_time;
    u16 last_modification_date;
    u32 CRC32;                      // of uncompressed data
    u32 compressed_size;
    u32 uncompressed_size;
    u16 file_name_length;
    u16 extra_field_length;
    char file_name[];
    char extra_field[];
} ZIP_FILE_HEADER;
