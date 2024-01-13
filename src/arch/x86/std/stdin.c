#include "stdin.h"
#include "stdout.h"

#include "../utils/controller.h"
#include "../utils/string.h"


void setCursorPosition(int row, int col) {
    int position = row * 80 + col; // Assuming 80 columns

    // Send command byte to VGA registers
    outb(0x3D4, 0x0F); // VGA control register: set low cursor byte
    outb(0x3D5, (unsigned char)(position & 0xFF)); // Low byte

    outb(0x3D4, 0x0E); // VGA control register: set high cursor byte
    outb(0x3D5, (unsigned char)((position >> 8) & 0xFF)); // High byte
}


// Keyboard mapping table for standard US keyboard
char keyMap[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t',
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, ' ', 0,
};

// Function to check if keyboard input is available
int isKeyboardInputAvailable() {
    // Check the status port's 0th bit (bit 0) to see if there's data to be read
    unsigned char status = inb(KEYBOARD_STATUS_PORT);
    return status & 0x1;
}

char readKeyboardInput() {
    while (!isKeyboardInputAvailable());

    unsigned char data = inb(KEYBOARD_DATA_PORT);

    // we only read non holding scan keys
    if (data & 0x80) {
        // This is a break code, ignore it
        return 0;
    }
    // print the scan code for debug
    char* b;
    intToString(data,b);
    puts(23,78,b,background_color);

    // return the corresponding character to the key
    return keyMap[data];
}
