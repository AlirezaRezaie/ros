#ifndef STDIN_H
#define STDIN_H

// Define the keyboard ports
#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

int isKeyboardInputAvailable();
char readKeyboardInput();
unsigned char rtc_read(unsigned char reg);
char codeToChar(char scan_code);
#endif
