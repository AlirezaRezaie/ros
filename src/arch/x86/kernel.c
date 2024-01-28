#include "std/stdout.h"
#include "terminal/terminal.h"

// Your kernel_start function
void kernel_start(){
    //clearScreen();
    prepare_terminal();
    while(1) {
        fill_screen();
        terminal();
    }
}