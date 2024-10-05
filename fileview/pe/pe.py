from bytetypes import *

IMAGE_DOS_HEADER: Struct = Struct({
    "e_magic":      u16,
    "e_cblp":       u16,
    "e_cp":         u16,
    "e_crlc":       u16,
    "e_cparhdr":    u16,
    "e_minalloc":   u16,
    "e_maxalloc":   u16,
    "e_ss":         u16,
    "e_sp":         u16,
    "e_csum":       u16,
    "e_ip":         u16,
    "e_cs":         u16,
    "e_lfarlc":     u16,
    "e_ovno":       u16,
    "e_res":        Array(u16, 4),
    "e_oemid":      u16,
    "e_oeminfo":    u16,
    "e_res2":       Array(u16, 10),
    "e_lfanew":     i32,
})

"""
IMAGE_OPTIONAL_HEADER: Union = Union({
    "pe32": Struct({}),
    "pe64": Struct({}),
})
"""

PE: Struct = Struct({
    "DosHdr": IMAGE_DOS_HEADER,
})
