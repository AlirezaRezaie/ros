[org 0x7c00]
; we can also alter the data segment register (ds) accordingly:
; mov ds, 0x7c0 (it will be 0x7c00 because address bus is 20-bit)

KERNEL_LOCATION equ 0x1000
BOOT_DISK equ 0

; setting up the stack and tiny memory model
xor ax, ax
mov es, ax
mov ds, ax
mov bp, 0x8000
mov sp, bp


; loading the kernel in memory location 0x1000
call read_disk

; ; Set up VESA graphics mode (example: mode 0x101 - 640x480, 16 colors)
; mov ax, 0x4F02     ; VESA function to set video mode
; mov bx, 0x101      ; Mode number for desired resolution/color depth
; int 0x10           ; Call BIOS interrupt to set the video mode

; initialize protected mode
init_pm:

    ; clear the screen using bios before disabling it
    mov ax, 0x0003 
    int 10h

    ; clear interrupts
    mov bx,suc
    ;call print_string
    
    ; some delay just for looking cool :)
    ;call delay
    ;mov ax, 0x0003
    ;int 10h
 
    cli
    ; this instruction loads the gdt location and size into the gdtr (gdt register) in the cpu
    lgdt [GDT_descriptor]

    ; changing the first bit of cr0 register (0th control register) which corresponds to [ Protected Mode Enable ]
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    ; far jump!!
    jmp CODE_SEG:start_protected_mode

%include "gdt.asm"
%include "read_disk.asm"
%include "print_string.asm"
%include "delay.asm"

; this tells the assembeler (in this case nasm) to compile the
; code to 32 bit machine code now on
[bits 32]
start_protected_mode:

    ; changing stack and memory segments model
    mov eax, DATA_SEG
	mov ds, eax
	mov ss, eax
	mov es, eax
	mov fs, eax
	mov gs, eax

	mov ebp, 0x8000000		; 32 bit stack base pointer
	mov esp, ebp

    jmp KERNEL_LOCATION

suc:
    db "entering 32-bit mode...",0
jmp $



times 510-($-$$) db 0
dw 0xaa55
