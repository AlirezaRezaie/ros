ENTRY(_start)

SECTIONS
{
    . = 0x1000;

    .text :
    {
        *(.text)
    }

    .data :
    {
        *(.data)
    }
    
    . += 0xF00000;

    .bss :
    {
        *(.bss)
    }
    


}
