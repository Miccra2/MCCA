.intel_syntax noprefix
.section .text
.global _start
_start:
    # write
    mov rax, 0          # write(
    mov rdi, 1          #   stdout,
    mov rsi, hello      #   hello,
    mov rdx, 22         #   sizeof(hello)
    syscall             # )
    
    # exit
    mov rax, 60         # exit(
    mov rdi, 0          #   EXIT_SUCCESS
    syscall             # )

.section .rodata
hello: .string "Hello, from assembly!\n"
