#include "string.h"
#include "controller.h"

// Function to read from RTC
unsigned char rtc_read(unsigned char reg) {
    while (inb(0x71) & 0x80); // Check bit 7 (UIP) of register A

    // Read the value from the specified register
    outb(0x70, reg);
    return inb(0x71);
}

void get_time(unsigned char* buffer){
    int buf_size = 0;

    for (int i = 4; i >= 0; i -= 2)
    {
        unsigned char bcd = rtc_read(i);

        unsigned char highsec = (bcd >> 4) & 0x0F;
        unsigned char lowsec = bcd & 0x0F;

        unsigned char low[3]; // Assuming min will be within 0-59 range
        unsigned char high[3]; // Assuming min will be within 0-59 range

        intToString((unsigned int)lowsec, low);
        intToString((unsigned int)highsec, high);


        add_to_string(high,buffer,&buf_size);
        add_to_string(low,buffer,&buf_size);
        add_to_string(":",buffer,&buf_size);

    }


}