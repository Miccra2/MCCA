def dump(data: bytes, offset: int | None = None, length: int | None = None) -> str:
    start: int = offset
    start -= start%16
    end: int = len(data)

    if offset == None:
        start = 0

    if isinstance(length, int):
        end = offset + length
        if end - start > 16:
            end += end % 16

    result: str = ""
    for i in range(start, end, 16):
        result += "%.8X: " % i
        subres: str = "|"
        
        for j in range(16):
            if i+j > len(data) - 1 or i+j < offset or i+j >= offset+length:
                result += "   "
                subres += " "
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
        print("[Error] InputArguments: To few arguments given, please provide more arguments!")
        usage()
        exit(1)

    data: bytes
    try:
        with open(argv[1], "rb") as file:
            data = file.read()
    except IOError:
        print(f"[Error] InputArguments: Invalid file '{argv[1]}' given, please provide a valid file!")
        usage()
        exit(1)

    offset: int = 0
    length: int = 0
    if len(argv) >= 3:
        offset = int(argv[2])
    if len(argv) >= 4:
        length = int(argv[3])
    if length == 0:
        length = len(data) - offset - 1

    print(dump(data, offset, length))

    exit(0)
