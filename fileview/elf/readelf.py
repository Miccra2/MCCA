EI_CLASS: tuple[str] = ("ELFCLASSNONE", "ELFCLASS32", "ELFCLASS64")
EI_DATA: tuple[str] = ("ELFDATANONE", "ELFDATA2LSB", "ELFDATA2MSB")

def elfHdrInfo(data: bytes) -> None
    print("ELF_HEADER:")
    print("    u8  e_ident[16]:")
    print("        EI_MAGIC:      %.8X '%s'" % (data[:4], data[:4]))
    print("        EI_CLASS:      %i '%s'" % (data[4], EI_CLASS[data[4]]))
    print("        EI_DATA:       %i '%s'" % (data[5], EI_DATA[data[5]]))
    print("        EI_VERSION:    %i" % data[6])
    print("        EI_OSABI:      %i '%s'" % (data[7], EI_OSABI[data[7]]))
    print("        EI_ABIVERSION: %i" % data[8])
    print("        EI_PAD:        %.14X" % data[9:16])
    print("    u16  e_type:     %i '%s'" % (int.from_bytes(data[16:18])))
    print("    u16  e_machine:  %i '%s'" % (int.from_bytes(data[18:20])))
    print("    u")

def readelf(path: str) -> None:
    data: bytes = b""
    with open(path, "rb") as file:
        data = file.read()

    elfHdrInfo(data[0:64])
