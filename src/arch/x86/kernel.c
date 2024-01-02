#include "std/stdin.h"
#include "std/stdout.h"
#include "utils/time.h"


// Your kernel_start function
void kernel_start(){
    // Now, let's handle keyboard input
    char *buf[1];
    char *linefeed = "type> \0";
    char *welcome_msg = "welcome to my 32 bit operating system :).n";
    print(1, welcome_msg);
    print(2, linefeed);
    setCursorPosition(row,col);

    while(1) {
        // Check for keyboard input
        if (isKeyboardInputAvailable()) {
            char keyPressed = readKeyboardInput();
            // Process the key here as needed
            // For now, just print the key to the screen
            char keyString[3] = { keyPressed };
            if (keyPressed == '\n'){
                print(3, ".n");
                print(2, linefeed);
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
        unsigned char bfr[20];
        get_time(bfr);
        puts(24, 72, bfr);

    }
}
