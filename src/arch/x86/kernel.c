#include "std/stdout.h"
#include "utils/time.h"
#include "utils/string.h"
#include "utils/math.h"
#include "keyboard.h"

// Your kernel_start function
void kernel_start(){
    // Now, let's handle keyboard input
    clearScreen();

    char *welcome_msg = "welcome to my 32 bit operating system :) \0";
    char *banner = fill_string(' ',80);

    int current_time = get_timestamp();
    background_color = 113;

    print(2, linefeed);
    puts(24,0, banner,70);
    puts(0,0, welcome_msg,5);

    setCursorPosition(row,col);

    while(1) {
        fill_screen();
        handle_keyboard();
        
        unsigned char time_bfr[20];
        get_time(time_bfr);
        puts(24, 62, time_bfr,75);

        char* unix_t;
        intToString(get_timestamp()/1000,unix_t);
        puts(1,60,"time ",75);
        puts(1,65,unix_t,75);

        if (get_timestamp() - current_time > 3 * pow(10,8)){
            puts(24,0,welcome_msg,75);
            shift_string_right(welcome_msg,strlen(welcome_msg));
            current_time = get_timestamp();
        }
    }
}
