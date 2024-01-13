#include "std/stdin.h"
#include "std/stdout.h"
#include "utils/time.h"
#include "utils/string.h"
#include "utils/math.h"

void executor(char* command){
    char** split_command = (char**) 0x100000;
    split_string(command,' ',split_command);
    
    if (str_cmpr(command,"clear")){
        row = 0;
        col = 0;
        clearScreen();
        setCursorPosition(20, 20);
    }else if(str_cmpr(command,"info")){
        print(2,"yes ok ;].n.n");
    }else if(str_cmpr(split_command[0],"setcolor")){
        int color = stringToInt(split_command[1]);
        // puts(20,40,split_command[1],6);
        if (strlen(split_command[1]) == 3){
            background_color = color;
            print(2,"ok setting color.n");
  
        }else{
            print(2,"int should be only 2 digit .n");
        }
    }
}

// Your kernel_start function
void kernel_start(){
    // Now, let's handle keyboard input
    clearScreen();

    char *cmd_buffer = (char*) 0xf000;
    int cmd_buf_size = 0;
    int max_size = 100; // Adjust the maximum buffer size as needed
    char *buf[1];
    char *linefeed = ".ntype> \0";
    char *welcome_msg = "welcome to my 32 bit operating system :)";
    char *banner = fill_string(' ',80);
    char *text = "this is america so be carefull \0";
    int txt_row = 20;
    int txt_col = 20;
    
    int current_time = get_timestamp();

    print(2, linefeed);
    puts(24,0, banner,70);
    puts(0,0, welcome_msg,5);

    setCursorPosition(row,col);

    while(1) {
        fill_screen();

        // Check for keyboard input
        if (isKeyboardInputAvailable()) {
            char keyPressed = readKeyboardInput();
            // add the character to the cmd buffer
            char keyString[3] = { keyPressed };
            add_to_string(keyString,cmd_buffer,&cmd_buf_size);
            if (keyPressed == '\n'){
                // check for any commands and execute them
                int prev_row = row;

                // finish the buffer to print
                cmd_buffer[cmd_buf_size-1] = '\0';

                print(3, ".n");
                executor(cmd_buffer);

                // print(5,cmd_buffer);
                clear_buffer(cmd_buffer,max_size);
                cmd_buf_size = 0; 

                print(background_color, linefeed);

                if (row >= 21){
                    for (int i = 0; i < row - prev_row; i++)
                    {
                        shiftScreenUp();
                    }
                    
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
        
        unsigned char time_bfr[20];
        get_time(time_bfr);
        puts(24, 62, time_bfr,75);

        char* unix_t;
        intToString(get_timestamp(),unix_t);
        puts(1,60,"time ",75);
        puts(1,65,unix_t,75);

        if (get_timestamp() - current_time > 3 * pow(10,8)){
            puts(24,0,text,75);
            shift_string_right(text,strlen(text));
            current_time = get_timestamp();
        }
    }
}
