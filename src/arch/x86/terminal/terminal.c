#include "terminal.h"
#include "std/stdout.h"
#include "std/stdin.h"
#include "utils/string.h"
#include "utils/controller.h"
#include "utils/time.h"
#include "utils/math.h"


int cmd_buf_size = 0;
int max_size = 100; // Adjust the maximum buffer size as needed
char *buf[1];
char *linefeed = "type> ";
char *welcome_msg = "welcome to my 32 bit operating system :) \0";
int current_time = 10000;

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
    printf("command not found: %c",full_command);
}

void prepare_terminal(){
    row = 0;
    col = 0;
    char *banner = fill_string(' ',80);

    printf("\n %c",linefeed);
    //puts(0,0, welcome_msg ,5);
    puts(24,0, banner,70);

    setCursorPosition(row,col);

}

void open_blank_page(){

}


void terminal(char keyPressed){
    char *cmd_buffer = (char*) 0x7f5500;
    // Check for keyboard input
    if (keyPressed != '\0'){
        keyPressed = codeToChar(keyPressed);
        // add the character to the cmd buffer
        add_char_to_string(keyPressed,cmd_buffer,&cmd_buf_size,100);
        char keyString[1] = { keyPressed };

        if (keyPressed == '\n'){
            // check for any commands and execute them
            int prev_row = row;
            // finish the buffer to print
            cmd_buffer[cmd_buf_size-1] = '\0';
            cmd_buffer[cmd_buf_size] = '\0';

            printf("\n\0");
            if (strlen(cmd_buffer) > 0){
                executor(cmd_buffer);
            }

            clear_buffer(cmd_buffer,max_size);
            cmd_buf_size = 0; 

            printf("\n %c",linefeed);

            if (row > 21){
                shiftScreenUp(row - prev_row);
                row = 20;
                col = 6;
                printf(linefeed);
            }
        }
        // linefeed protector and delete handler
        else if(keyPressed == '\b' && col > 6){
            video -= 2;  // Move the pointer back by two positions (assuming each character takes two bytes)
            *video = ' ';  // Update the value
            *(video + 1) = background_color;  // Null-terminate the character
            col -= 1;
            cmd_buffer[cmd_buf_size -2] = '\0';
            cmd_buf_size -=2;
        }
        else{
            printf(keyString);
        }
        setCursorPosition(row,col);
    }

    unsigned char time_bfr[20];

    get_time(time_bfr);
    puts(24, 62, time_bfr,75);

    char unix_t[40];
    intToString(get_timestamp(),unix_t);
    puts(1,60,"time ",75);
    puts(1,65,unix_t,75);

    if (get_timestamp() - current_time > 3 * pow(10,8)){
        puts(24,0,welcome_msg,75);
        shift_string_right(welcome_msg,strlen(welcome_msg));
        current_time = get_timestamp();
    }
};