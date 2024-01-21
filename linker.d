ENTRY(_start)

SECTIONS
{
   . = 0x1000;

   .text :
   {
      *(.text)
   }

   .bss :
   {
      *(.bss)
   }

   .data :
   {
      *(.data)
   }
}
