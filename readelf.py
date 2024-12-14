#!/usr/bin/env python3.12
from typing import Self
import sys

USAGE: str = "Usage: python readelf.py [file]\n    file - elf format file executable"

class IntegerType:
    def __init__(self, length: int, byteorder: str = "little", signed: bool = True) -> None:
        self.value: bytes = bytes((0 for _ in range(length)))
        self.length = length
        self.byteorder = byteorder
        self.signed = signed

    def __int__(self) -> int:
        return int.from_bytes(self.value, byteorder=self.byteorder, signed=self.signed)

    def __bytes__(self) -> bytes:
        return self.value
    
    def __str__(self) -> str:
        return f"{int(self)}"

    def __repr__(self) -> str:
        return str(self)

    def __add__(self, other) -> Self:
        self.set(int(self) + int(other))
        return self

    def __sub__(self, other) -> Self:
        self.set(int(self) - int(other))
        return self

    def __mul__(self, other) -> Self:
        self.set(int(self) * int(other))
        return self

    def __div__(self, other) -> Self:
        self.set(int(self) * int(other))
        return self

    def __mod__(self, other) -> Self:
        self.set(int(self) % int(other))
        return self

    def __pow__(self, other) -> Self:
        self.set(int(self) ** int(other))
        return self

    def set(self, value: bytes | int) -> None:
        if isinstance(value, bytes):
            self.value = value
        elif isinstance(value, int):
            self.value = value.to_bytes(length=self.length, byteorder=self.byteorder, sigend=self.signed)
        else:
            assert False, f"ERROR: Invalid type ({type(value)}) of value in IntegerType!"

class struct:
    def __new__(self, cls) -> Self:
        self.cls = cls()
        print(vars(cls))
        return self

    def __init__(self, cls) -> None:
        sels.cls = cls()
        print(vars(cls))

    def __repr__(self) -> str:
        return vars(self.cls)

i8 = IntegerType(1, "little", True)
i16 = IntegerType(2, "little", True)
i32 = IntegerType(4, "little", True)
i64 = IntegerType(8, "little", True)
u8 = IntegerType(1, "little", False)
u16 = IntegerType(2, "little", False)
u32 = IntegerType(4, "little", False)
u64 = IntegerType(8, "little", False)

@struct
class E_IDENT:
    def __init__(self) -> None:
        self.ei_mag0: u8 = u8
        self.ei_mag1: u8 = u8
        self.ei_mag2: u8 = u8
        self.ei_mag3: u8 = u8
        self.ei_class: u8 = u8
        self.ei_data: u8 = u8
        self.ei_version: u8 = u8
        self.ei_osabi: u8 = u8
        self.ei_abiversion: u8 = u8
        self.ei_pad9: u8 = u8
        self.ei_pad10: u8 = u8
        self.ei_pad11: u8 = u8
        self.ei_pad12: u8 = u8
        self.ei_pad13: u8 = u8
        self.ei_pad14: u8 = u8
        self.ei_pad15: u8 = u8

@struct
class ELF_HEADER64:
    def __init__(self) -> None:
        self.e_ident:     E_IDENT = E_IDENT()
        self.e_type:      u16 = u16
        self.e_machine:   u16 = u16
        self.e_version:   u32 = u32
        self.e_entry:     u64 = u64
        self.e_phoff:     u64 = u64
        self.e_shoff:     u64 = u64
        self.e_flags:     u32 = u32
        self.e_ehsize:    u16 = u16
        self.e_phentsize: u16 = u16
        self.e_phnum:     u16 = u16
        self.e_shentsize: u16 = u16
        self.e_shnum:     u16 = u16
        self.e_shstridx:  u16 = u16

def get_elf_header64(data: bytes) -> ELF_HEADER64:
    if not isinstance(data, bytes):
        assert False, f"ERROR: Invalid type ({type(data)}) of data in get_elf_header64!"
    return ELF_HEADER64(E_IDENT(data[0:16][:]),
                      data[16:18], 
                      data[18:20], 
                      data[20:24], 
                      data[24:32], 
                      data[32:40], 
                      data[40:48], 
                      data[48:52], 
                      data[52:54], 
                      data[54:56], 
                      data[56:58], 
                      data[58:60], 
                      data[60:62], 
                      data[62:64])

def read_file(path: str) -> None:
    if not isinstance(path, str):
        assert False, f"ERROR: Invalid type ({type(path)}) of path in read_file!"
    data: bytes
    try:
        with open(path, "rb") as file:
            data = file.read()
    except FileNotFoundError:
        assert False, f"ERROR: Could not open file \"{path}\"!"
    header = get_elf_header64(data[:64])

    A = {f: vars(header)[f] for f in vars(header)}
    for a in A:
        print(f"{a}: {A[a]}")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        assert False, "ERROR: To few input arguments given, please provide more input arguments!\n" + USAGE
    read_file(sys.argv[1])
