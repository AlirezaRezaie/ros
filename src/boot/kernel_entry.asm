global _start

_start:
    [bits 32]
    [extern kernel_start]
    call kernel_start
    jmp $
