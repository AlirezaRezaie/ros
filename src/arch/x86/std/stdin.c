#include "stdin.h"
#include "../utils/controller.h"


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

// Function to read keyboard input
char readKeyboardInput() {
    // Wait until the input is available
    while (!isKeyboardInputAvailable());

    // Read the data from the keyboard data port
    unsigned char data = inb(KEYBOARD_DATA_PORT);
    return keyMap[data];
}