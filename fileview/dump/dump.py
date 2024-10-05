def dump(data: bytes, offset: int | None = None, length: int | None = None) -> str:
    start: int = offset
    end: int = 0
    
    start -= start % 16
    if offset == None:
        start = 0

    if length == None:
        end = len(data)
    else:
        end = start + length

    result: str = ""
    for i in range(start, end, 16):
        chars: str = "|"
        result += "%.8X: " % i
        
        for j in range(16):
            if i+j < offset or i+j > end:
                result += "   "
                chars += " "
                continue
            
            if data[i+j] <= 0x20 and data[i+j] >= 0x7E:
                chars += " "
            else:
                chars += ord(data[i+j])
            
            result += "%.2X" % data[i+j]

        result += chars + "|\n"

    return result

if __name__ == "__main__":
    dump()
