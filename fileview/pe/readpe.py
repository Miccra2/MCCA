#!/usr/bin/env python3.12
from pe import *

class Pe:
    def __init__(self, path: str) -> None:
        self.path = path

    def read(self) -> PE:
        data: bytes = b""
        TmpDosHdr: IMAGE_DOS_HEADER = IMAGE_DOS_HEADER
        
        with open(self.path, "rb") as file:
            data = file.read()
        
        TmpDosHdr.set(data)
        return TmpDosHdr

if __name__ == "__main__":
    pe: Pe = Pe("/home/miccra/Downloads/GenshinImpact_install_ua_f5d2ee7ed4f4.exe")
    doshdr = pe.read()
    doshdr.get()
    #print("IMAGE_DOS_HEADER")
    #for i in doshdr.fields:
    #    print(f"    {i}: %.4X" % int.from_bytes(bytes(doshdr.fields[i])))
