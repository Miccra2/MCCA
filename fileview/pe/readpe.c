#include <stdio.h>

#include "pe.h"

#define USAGE "Usage: readpe <file>\n"

void DosHdrInfo(IMAGE_DOS_HEADER *DosHdr) {
    printf("IMAGE_DOS_HEADER:\n");
    printf("  e_magic:    %.4X\n", DosHdr->e_magic);
    printf("  e_cblp:     %.4X\n", DosHdr->e_cblp);
    printf("  e_cp:       %.4X\n", DosHdr->e_cp);
    printf("  e_crlc:     %.4X\n", DosHdr->e_crlc);
    printf("  e_cparhdr:  %.4X\n", DosHdr->e_cparhdr);
    printf("  e_minalloc: %.4X\n", DosHdr->e_minalloc);
    printf("  e_maxalloc: %.4X\n", DosHdr->e_maxalloc);
    printf("  e_ss:       %.4X\n", DosHdr->e_ss);
    printf("  e_sp:       %.4X\n", DosHdr->e_sp);
    printf("  e_csum:     %.4X\n", DosHdr->e_csum);
    printf("  e_ip:       %.4X\n", DosHdr->e_ip);
    printf("  e_cs:       %.4X\n", DosHdr->e_cs);
    printf("  e_lfarlc:   %.4X\n", DosHdr->e_lfarlc);
    printf("  e_ovno:     %.4X\n", DosHdr->e_ovno);
    printf("  e_res:      %.4X %.4X %.4X %.4X\n", 
            DosHdr->e_res[0], DosHdr->e_res[1], 
            DosHdr->e_res[2], DosHdr->e_res[3]);
    printf("  e_oemid:    %.4X\n", DosHdr->e_oemid);
    printf("  e_oeminfo:  %.4X\n", DosHdr->e_oeminfo);
    printf("  e_res2:     %.4X %.4X %.4X %.4X %.4X"
            " %.4X %.4X %.4X %.4X %.4X\n", DosHdr->e_res2[0], 
            DosHdr->e_res2[1], DosHdr->e_res2[2], DosHdr->e_res2[3],
            DosHdr->e_res2[4], DosHdr->e_res2[5], DosHdr->e_res2[6],
            DosHdr->e_res2[7], DosHdr->e_res2[8], DosHdr->e_res2[9]);
    printf("  e_lfanew:   %.8X\n", DosHdr->e_lfanew);
}

void FileHdrInfo(IMAGE_FILE_HEADER *FileHdr) {
    printf("IMAGE_FILE_HEADER:\n");
    printf("  Machine:              %.4X\n", FileHdr->Machine);
    printf("  NumberOfSections:     %.4X\n", FileHdr->NumberOfSections);
    pirntf("  TimeDateStamp:        %.8X\n", FileHdr->TimeDateStamp);
    printf("  PointerToSymbolTabel: %.8X\n", FileHdr->PointerToSymbolTabel);
    printf("  NumberOfSymbols:      %.8X\n", FileHdr->NumberOfSymbols);
    printf("  SizeOfOptionalHeader: %.4X\n", FileHdr->SizeOfOptionalHeader);
    pirntf("  Characteristics:      %.4X\n", FileHdr->Characteristics);
}

void DataDirInfo(IMAGE_DATA_DIRECTORY *DataDir) {
    printf("IMAGE_DATA_DIRECTORY:\n");
    printf("  VirtualAddress: %.8X\n", DataDir->VirtualAddress);
    printf("  Size:           %.8X\n", DataDir->Size);
}

void OptHdr32Info(IMAGE_OPTIONAL_HEADER32 *OptHdr) {
    printf("IMAGE_OPTIONAL_HEADER32:\n");
    printf("  Magic:                       %.4X\n", OptHdr->Magic);
    printf("  MajorLinkerVersion:          %.2X\n", OptHdr->MajorLinkerVersion);
    printf("  MinorLinkerVersion:          %.2X\n", OptHdr->MinorLinkerVersion);
    printf("  SizeOfCode:                  %.8X\n", OptHdr->SizeOfCode);
    printf("  SizeOfInitializedData:       %.8X\n", 
            OptHdr->SizeOfInitializedData);
    printf("  SizeOfUninitializedData:     %.8X\n", 
            OptHdr->SizeOfUninitializedData);
    printf("  AddressOfEntryPoint:         %.8X\n", 
            OptHdr->AddressOfEntryPoint);
    printf("  BaseOfCode:                  %.8X\n", OptHdr->BaseOfCode);
    printf("  BaseOfData:                  %.8X\n", OptHdr->BaseOfData);
    printf("  ImageBase:                   %.8X\n", OptHdr->ImageBase);
    printf("  SectionAlignment:            %.8X\n", OptHdr->SectionAlignment);
    printf("  FileAlignment:               %.8X\n", OptHdr->FileAlignment);
    printf("  MajorOperatingSystemVersion: %.4X\n", 
            OptHdr->MajorOperatingSystemVersion);
    printf("  MinorOperatingSystemVersion: %.4X\n", 
            OptHdr->MinorOperatingSystemVersion);
    printf("  MajorImageVersion:           %.4X\n", OptHdr->MajorImageVersion);
    printf("  MinorImageVersion:           %.4X\n", OptHdr->MinorImageVersion);
    printf("  MajorSubsystemVersion:       %.4X\n", 
            OptHdr->MajorSubsystemVersion);
    printf("  MinorSubsystemVersion:       %.4X\n",
            OptHdr->MinorSubsystemVersion);
    printf("  Win32VersionValue:           %.8X\n", OptHdr->Win32VersionValue);
    printf("  SizeOfImage:                 %.8X\n", OptHdr->SizeOfImage);
    printf("  SizeOfHeaders:               %.8X\n", OptHdr->SizeOfHeaders);
    printf("  CheckSum:                    %.8X\n", OptHdr->CheckSum);
    printf("  Subsystem:                   %.4X\n", OptHdr->Subsystem);
    printf("  DllCharacteristics:          %.4X\n", OptHdr->DllCharacteristics);
    printf("  SizeOfStackReserve:          %.8X\n", OptHdr->SizeOfStackReserve);
    printf("  SizeOfStackCommit:           %.8X\n", OptHdr->SizeOfStackCommit);
    printf("  SizeOfHeapReserve:           %.8X\n", OptHdr->SizeOfHeapReserve);
    printf("  SizeOfHeapCommit:            %.8X\n", OptHdr->SizeOfHeapCommit);
    printf("  LoaderFlags:                 %.8X\n", OptHdr->LoaderFlags);
    printf("  NumberOfRvaAndSizes:         %.8X\n", 
            OptHdr->NumberOfRvaAndSizes);
    for (u8 i = 0; i < IMAGE_NUMBEROF_DIRECOTRY_ENTRIES; i++) {
        printf("\n---------------------------------------------\n");
        DataDirInfo(&OptHdr->DataDirectory[i]);
    }
}

void OptHdr64Info(IMAGE_OPTIONAL_HEADER64 *OptHdr) {
    printf("IMAGE_OPTIONAL_HEADER64:\n");
    printf("  Magic:                       %.4X\n", OptHdr->Magic);
    printf("  MajorLinkerVersion:          %.2X\n", OptHdr->MajorLinkerVersion);
    printf("  MinorLinkerVersion:          %.2X\n", OptHdr->MinorLinkerVersion);
    printf("  SizeOfCode:                  %.8X\n", OptHdr->SizeOfCode);
    printf("  SizeOfInitializedData:       %.8X\n", 
            OptHdr->SizeOfInitializedData);
    printf("  SizeOfUninitializedData:     %.8X\n", 
            OptHdr->SizeOfUninitializedData);
    printf("  AddressOfEntryPoint:         %.8X\n", 
            OptHdr->AddressOfEntryPoint);
    printf("  BaseOfCode:                  %.8X\n", OptHdr->BaseOfCode);
    printf("  ImageBase:                   %.16X\n", OptHdr->ImageBase);
}

void parsepe(FILE *pf) {
    IMAGE_DOS_HEADER DosHdr;
    fread(&DosHdr, 1, sizeof(DosHdr), pf);

    if (DosHdr.e_magic != DOSHDR_MAGIC) {
        return;
    }

    printf("IMAGE_DOS_HEADER:\n");
    printf("  e_magic: %.4X\n", DosHdr.e_magic);
    printf("  e_lfanew: %.8X\n", DosHdr.e_lfanew);

    DosHdrInfo(&DosHdr);
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
