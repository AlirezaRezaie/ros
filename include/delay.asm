delay:
    mov cx, 30 ; 3 seconds
    mov dx, 10
    mov ah, 0x86
    int 15h
    ret