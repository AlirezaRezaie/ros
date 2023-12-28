; must be at the end of real mode code
; this is the segments configurations
GDT_start:
    ;* each segment descriptor is 8 bytes *
    
    ; offset 0x0 (0 bytes)
    null_descriptor:
        dd 0x0
        dd 0x0

    ; offset 0x8 (8 bytes)
    code_descriptor:
        dw 0xffff ; segment limit first 0-15 bits
        dw 0x0    ; base first 0-15 bits
        db 0x0    ; base 16-23 bits

        ; access (present, ring 0, code segment, executable, direction 0, readable)
        db 10011010b
        ; granularity (4k pages, 32-bit pmode) + limit (16-19)
        db 11001111b

        db 0x0    ; base 24-31 bits

    ; offset 0x10 (16 bytes)
    data_descriptor:
        dw 0xffff ; segment limit first 0-15 bits
        dw 0x0    ; base first 0-15 bits
        db 0x0    ; base 16-23 bits

        ; (pres,priv,type)4,(Type flags)4
        db 10010010b
        ; other flags
        db 11001111b

        db 0x0    ; base 24-31 bits

GDT_end:

GDT_descriptor:
    dw GDT_end - GDT_start - 1 ; size of the gdt
    dd GDT_start ; gdt location at the memory

;useful constants
CODE_SEG equ code_descriptor - GDT_start
DATA_SEG equ data_descriptor - GDT_start