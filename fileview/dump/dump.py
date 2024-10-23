def dump(data: bytes, offset: int | None = None, length: int | None = None) -> str:
    start: int = 0
    end: int = 0

    if isinstance(offset, int):
        start = offset

        if start >= 16:
            start -= start%16

    if isinstance(length, int):
        end = offset + length

    result: str = ""
    for i in range(start, end, 16):
        result += "%.8X: " % i
        subres: str = "|"
        for j in range(16):
            if i+j >= len(data) or i+j >= offset+length or i+j < offset:
                result += "   "
                subres += "."
                continue
            
            if data[i+j] >= 0x20 and data[i+j] <= 0x7E:
                subres += chr(data[i+j])
            else:
                subres += "."

            result += "%.2X " % data[i+j]

        result += subres + "|\n"

    return result

if __name__ == "__main__":
    from sys import exit, argv

    def usage() -> None:
        print("Usage: dump.py file [offset] [length]")

    if len(argv) < 2:
        print("ERROR: To few input arguments given, please provide more input arguments")
        usage()
        exit(1)

    data: bytes = b""
    try:
        with open(argv[1], "rb") as file:
            data = file.read()
    except IOError:
        print("ERROR: Invalid file '%s' given, please provide a valid file!" % argv[1])
        usage()
        exit(1)

    offset: int = 0
    length: int = 0
    
    if len(argv) > 2:
        offset = int(argv[2])
    if len(argv) > 3:
        length = int(argv[3])
    if length > len(data):
        length = len(data) - offset

    print("path: '%s'" % argv[1])
    print("offset: %i" % offset)
    print("length: %i" % length)
    print(dump(data, offset, length))
