read_disk:

    ; bios read functions
    mov ah, 0x02

    ; adjust as needed (as big as the kernel size)
    mov al, 40

    ; chs addressing
    mov ch, 0x00 ; cylender
    mov dh, 0x00 ; head
    mov cl, 0x02 ; sector (reading the first sector after the boot sector sectors start at 1)


    ; setting the bx to the address we want to load our read disk
    mov bx, KERNEL_LOCATION

    mov dl, BOOT_DISK

    int 0x13  
    jc disk_error

    ; returning to the caller address
    ret

; error handler
disk_error:
    mov bx, error_msg
    call print_string
    jmp $

error_msg:
    ; null terminating string :)
    db "error reading disk",0