#include <stddef.h>
#include <stdint.h>

#include "std/stdout.h"
#include "std/stdin.h"

#include "utils/string.h"
#include "utils/memory.h"
#include "utils/controller.h"

#include "terminal/terminal.h"

void kernel_start() {
    zero_out_memory(BASE_ADDR, END_ADDR);
    prepare_mem_blocks();
    prepare_terminal();
    fill_screen();

    int start_term = 1;
    char keyPressed;

    while (1) {
        if (isKeyboardInputAvailable()) 
             keyPressed = readKeyboardInput();
        else keyPressed = '\0';

        terminal(keyPressed);
    }
}
