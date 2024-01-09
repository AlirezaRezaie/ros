#include "std/stdin.h"
#include "std/stdout.h"
#include "utils/time.h"
#include "utils/string.h"

void executor(char* command){
    if (str_cmpr(command,"clear")){
        row = 0;
        col = 0;
        clearScreen();
        setCursorPosition(20, 20);
    }else if(str_cmpr(command,"info")){
        print(2,"yes ok ;]");
    }
}
void clear_buffer(char* destination, int size) {
    // Overwrite the buffer content with null characters
    for (int i = 0; i < size; ++i) {
        destination[i] = '\0';
    }
}

char* fill_string(char character,int number){
    char *out;
    for (int i = 0; i < number; i++)
    {
        out[i] = character;
    }
    
    return out;
}

// Your kernel_start function
void kernel_start(){
    // Now, let's handle keyboard input

    char *cmd_buffer = (char*) 0xf000;
    int cmd_buf_size = 0;
    int max_size = 100; // Adjust the maximum buffer size as needed
    char *buf[1];
    char *linefeed = ".ntype> \0";
    char *welcome_msg = "welcome to my 32 bit operating system :)";
    char *banner = fill_string(' ',80);

    print(2, linefeed);
    puts(24,0, banner,70);

    setCursorPosition(row,col);
    
    while(1) {
        puts(0,0, welcome_msg,5);

        // Check for keyboard input
        if (isKeyboardInputAvailable()) {
            char keyPressed = readKeyboardInput();
            // add the character to the cmd buffer
            char keyString[3] = { keyPressed };
            add_to_string(keyString,cmd_buffer,&cmd_buf_size);
            if (keyPressed == '\n'){
                // check for any commands and execute them

                cmd_buffer[cmd_buf_size-1] = '\0';
                print(3, ".n");
                executor(cmd_buffer);

                // print(5,cmd_buffer);
                clear_buffer(cmd_buffer,max_size);
                cmd_buf_size = 0;
                

                print(2, linefeed);

                if (row >= 21){
                    shiftScreenUp();
                    shiftScreenUp();

                    row = 20;
                    col = 6;
                    print(2, linefeed);

                }
            }
            // linefeed protector and delete handler
            else if(keyPressed == '\b' && col > 6){
                *video-- = ' ';
                *video-- = 0;
                col -= 1;
            }
            else{
                print(7, keyString);
            }
            setCursorPosition(row,col);

        }
        
        unsigned char time_bfr[20];
        get_time(time_bfr);
        puts(24, 62, time_bfr,75);


    }
}
