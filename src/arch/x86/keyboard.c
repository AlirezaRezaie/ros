#include "keyboard.h"
#include "std/stdout.h"
#include "std/stdin.h"
#include "utils/string.h"
#include "utils/controller.h"

char *cmd_buffer = (char*) 0xf000;
int cmd_buf_size = 0;
int max_size = 100; // Adjust the maximum buffer size as needed
char *buf[1];
char *linefeed = ".ntype> \0";

CommandMapping commands[] = {
    {"clear", clear},
    {"info", info},
    {"setcolor", setcolor},
    {"count", count},
};

void executor(char* full_command) {

    STRLIST str;
    str.list = (char**) 0x100000;
    split_string(full_command, &cmd_buf_size, ' ', &str);

    for (int i = 0; i < sizeof(commands) / sizeof(commands[0]); ++i) {
        if (str_cmpr(str.list[0], commands[i].command)) {
            CommandArguments args = {str.list[0], str.list[1]};
            commands[i].action(&args);  // Pass the address of the structure
            return;
        }
    }

    print(3," .n \0");
}

void handle_keyboard(){
    // Check for keyboard input
    if (isKeyboardInputAvailable()) {
        char keyPressed = readKeyboardInput();
        // add the character to the cmd buffer
        add_char_to_string(keyPressed,cmd_buffer,&cmd_buf_size,100);
        char keyString[2] = { keyPressed };

        if (keyPressed == '\n'){
            // check for any commands and execute them
            int prev_row = row;
            // finish the buffer to print
            cmd_buffer[cmd_buf_size-1] = '\0';
            cmd_buffer[cmd_buf_size] = '\0';

            executor(cmd_buffer);

            // print(5,cmd_buffer);
            clear_buffer(cmd_buffer,max_size);
            cmd_buf_size = 0; 

            print(background_color, linefeed);

            if (row > 21){
                shiftScreenUp(row - prev_row);
                row = 20;
                col = 6;
                print(background_color, linefeed);
            }
        }
        // linefeed protector and delete handler
        else if(keyPressed == '\b' && col > 6){
            video -= 2;  // Move the pointer back by two positions (assuming each character takes two bytes)
            *video = ' ';  // Update the value
            *(video + 1) = 0;  // Null-terminate the character
            col -= 1;
            cmd_buffer[cmd_buf_size -2] = '\0';
            cmd_buf_size -=2; 
        }
        else{
            print(background_color, keyString);
        }
        setCursorPosition(row,col);

    }
    
};