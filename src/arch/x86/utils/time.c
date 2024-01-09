#include "string.h"
#include "controller.h"

// Function to read from RTC
unsigned char rtc_read(unsigned char reg) {
    while (inb(0x71) & 0x80); // Check bit 7 (UIP) of register A

    // Read the value from the specified register
    outb(0x70, reg);
    return inb(0x71);
}

void bcd_to_string(unsigned char reg,unsigned char* high,unsigned char* low){
    unsigned char bcd = rtc_read(reg);
    intToString((unsigned int)(bcd >> 4) & 0x0F, high);
    intToString((unsigned int)bcd & 0x0F, low);
}

// TODO: add iran time support
void get_time(unsigned char* buffer){
    int buf_size = 0;

    unsigned char hour_high[3],hour_low[3];
    unsigned char min_high[3],min_low[3];
    unsigned char second_high[3],second_low[3];

    bcd_to_string(0x04,hour_high,hour_low);
    bcd_to_string(0x02,min_high,min_low);
    bcd_to_string(0x00,second_high,second_low);

    add_to_string("UTC TIME ",buffer,&buf_size);

    add_to_string(hour_high,buffer,&buf_size);
    add_to_string(hour_low,buffer,&buf_size);
    add_to_string(":",buffer,&buf_size);

    add_to_string(min_high,buffer,&buf_size);
    add_to_string(min_low,buffer,&buf_size);
    add_to_string(":",buffer,&buf_size);

    add_to_string(second_high,buffer,&buf_size);
    add_to_string(second_low,buffer,&buf_size);

}