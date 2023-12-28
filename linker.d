ENTRY(_start)

SECTIONS
{

   /* this makes the kernel binary addresses relative to where it's loaded from bootloader which is address 0x1000
   in short => all addresses (including jmp and etc.) will be relative to the 0x1000 to. */
   
   /* we can access custom symbols (memory location ) in c using the keyword extern 
      and use it here.
   */

   . = 0x1000;

   .text :
   {
      *(.text)

   }

   
   .data : { *(.data) }

   .bss : { *(.bss) }

}