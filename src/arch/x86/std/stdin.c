#include "stdin.h"

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
    unsigned char status = 0;
    asm volatile("inb %1, %0" : "=a"(status) : "Nd"(KEYBOARD_STATUS_PORT));
    return status & 0x1;
}

// Function to read keyboard input
char readKeyboardInput() {
    // Wait until the input is available
    while (!isKeyboardInputAvailable());

    // Read the data from the keyboard data port
    unsigned char data = 0;
    asm volatile("inb %1, %0" : "=a"(data) : "Nd"(KEYBOARD_DATA_PORT));
    return keyMap[data];
}

