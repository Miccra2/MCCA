import sys
from typing import Literal

class ByteType:
    def __init__(self,
                 size: int,
                 byteorder: Literal["little", "big"] = "little",
                 signed: bool = True) -> None:
        assert byteorder.lower() in ("little", "big"), f"[Error] ByteType: Unsupported byteorder '{byteorder}'!"
        self.size = size
        self.byteorder = byteorder.lower()
        self.signed = signed
        self.data = bytes(self.size)

    def __len__(self) -> int:
        return self.size
    
    def __int__(self) -> int:
        return int.from_bytes(self.data, byteorder=self.byteorder, signed=self.signed)
    
    def __bytes__(self) -> bytes:
        return self.data

    def set(self, data: bytes) -> None:
        # using: 'data[:len(data)]' for presrving bytes type if len(data) is one
        if self.byteorder == "big":
            self.data = data[:len(self)] if len(self) < len(data) else bytes(len(self) - len(data)) + data[:len(data)]
        elif self.byteorder == "little":
            self.data = data[:len(self)] if len(self) < len(data) else data[:len(data)] + bytes(len(self) - len(data))

    def get(self) -> bytes:
        return bytes(self)

class Array:
    def __init__(self, bytetype: ByteType, length: int) -> None:
        self.bytetype = bytetype
        self.length = length
        self.size = length * len(self.bytetype)
        self.data = bytes(self.size)

    def __len__(self) -> int:
        return self.size

    def __bytes__(self) -> bytes:
        return self.data

    def __setitem__(self, key: int, value: int | bytes | ByteType) -> None:
        value: bytes = bytes(value) if type(value) != bytes else value
        offset: int = self.length * len(self.bytetype)
        if len(self.bytetype) < len(value):
            self.data = self.data[:offset] + value + self.data[offset+len(self.bytetype):]
        else:
            self.data = self.data[:offset] + bytes(len(self) - offset)

    def __getitem__(self, key: int) -> ByteType:
        result: ByteType = self.bytetype
        result.set(self.data[key*self.length:key*self.length+len(self.bytetyp)])
        return result

    def set(self, data: bytes) -> None:
        self.data = data[:len(self)] if len(self) < len(data) else data[:len(data)] + bytes(len(self) - len(data))

    def get(self) -> bytes:
        return bytes(self)

class Struct:
    def __init__(self, fields: dict[str, ByteType]) -> None:
        self.fields = fields
        self.size = 0
        for key in self.fields:
            self.size += len(self[key])

    def __len__(self) -> int:
        return self.size

    def __bytes__(self) -> bytes:
        result: bytes = b""
        for key in self.fields:
            result += bytes(self[key].get())
        return result

    def __setitem__(self, key: str, value: int | bytes | ByteType) -> None:
        assert key in (i for i in self.fields), f"[Error] Struct: Key '{key}' is an invalid field!"
        value: bytes = bytes(value) if type(value) != bytes else value
        self.fields[key].set(value)

    def __getitem__(self, key: str) -> ByteType:
        assert key in (i for i in self.fields), f"[Error] Struct: Key '{key}' is an invalid field!"
        return self.fields[key]

    def set(self, data: bytes) -> None:
        offset: int = 0
        for key in self.fields:
            if offset < len(data) and len(self[key]) <= len(data[offset:]):
                self[key].set(data[offset:offset+len(self[key])])
            elif offset < len(data):
                self[key].set(data[offset:] + bytes(offset + len(self[key]) - len(data[offset:])))
            else:
                self[key].set(bytes(len(self[key])))

            a = [(i, self[i].get(), data[offset:offset+len(self[key])]) for i in self.fields]
            for i in a:
                print(i[0])
                print(i[1])
                print(i[2])
            print()
            offset += len(self[key])

    def get(self) -> bytes:
        return bytes(self)

del Literal

i8:  ByteType = ByteType(1, byteorder=sys.byteorder, signed=True)
i16: ByteType = ByteType(2, byteorder=sys.byteorder, signed=True)
i32: ByteType = ByteType(4, byteorder=sys.byteorder, signed=True)
i64: ByteType = ByteType(8, byteorder=sys.byteorder, signed=True)
u8:  ByteType = ByteType(1, byteorder=sys.byteorder, signed=False)
u16: ByteType = ByteType(2, byteorder=sys.byteorder, signed=False)
u32: ByteType = ByteType(4, byteorder=sys.byteorder, signed=False)
u64: ByteType = ByteType(8, byteorder=sys.byteorder, signed=False)
del sys
