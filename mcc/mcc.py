from sys import exit, argv
from dataclasses import dataclass

IOTA_COUNTER: int = 0
def iota(reset: bool = False) -> int:
    if reset:
        IOTA_COUNTER = 0
    result: int = IOTA_COUNTER
    IOTA_COUNTER += 1
    return result

def usage() -> None:
    print("Usage: mcc.py [com|sim] <file>")

@dataclass
class Text:
    line: int
    ptr: int
    cur: int
    length: int
    text: str

@dataclass
class CompilerFlags:
    mode: str
    text: Text

TOKEN_NONE: int = iota(True)
TOKEN_NUMBER: int = iota()
TOKEN_PLUS: int = iota()

def isnumberstart(char: str) -> bool:
    return ord(char) >= ord("0") and ord(char) <= ord("9")

def islabelstart(char: str) -> bool:
    return (
        char == "_" or
        (ord(char) >= ord("A") and ord(char) <= ord("Z")) or
        (ord(char) >= ord("a") and ord(char) <= ord("z"))
    )

def lentest(text: Text) -> bool:
    return text.cur < text.buffer.length

def cuttext(text: Text) -> str:
    result: str = text.buffer[text.ptr:text.cur]
    text.ptr = text.cur
    return result

@dataclass
class Token:
    type: int
    content: any

def lexer(flags: CompilerFlags) -> Tokens:
    tokens: list[Token] = []
    token: Token
    while lentest(flags.text):
        char: str = flags.text[i]
        match char:
            case "\n":
                line += 1
                token = Token()
                continue
            case "\r" | "\t" | " ":
                token = Token()
                continue
            case "+":
                token = Token()
                token.type = TOKEN_PLUS
                continue
            case _:

                # lex label
                if islabelstart(char):
                    while lentest(flags.text) and (islablestart(char) or 
                            (ord(char) >= ord("0") and ord(char) <= ord("9"))):
                        flags.text.cur += 1
                    cuttext(flags.text)
                
                # lex number
                if isnumberstart(char):
                    while lentest(flags.text) and char == "." or isnumberstart(char):
                        flags.text.cur += 1
                    cuttext(flags.text)

                print(f"[Error] Token: Invalid token '{flags.text[i]}'")
                exit(1)
        flags.text.cur += 1

if __name__ == "__main__":
    if len(argv) < 2:
        print("[Error] InputArguments: To few input arguments given!")
        usage()
        exit(1)

    flags: CompilerFlags = CompilerFlags()
    
    if not argv[1] in ("sim", "com"):
        print(f"[Error] InputArguments: Invalid subcommand '{argv[1]}' given!")
        usage()
        exit(1)

    flags.mode = argv[1]
    flags.text = Text()

    with open(argv[2], "r") as file:
        flags.text.buffer = file.read()

    flags.text.length = len(flags.text.buffer)
    flags.text.ptr = 0
    flags.text.cur = 0
    flags.text.line = 0
    lexer(flags)
