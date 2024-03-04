#include "stdout.h"
#include "../utils/controller.h"
#include "../utils/string.h"
#include <stdarg.h>

volatile char *video = (volatile char*)0xB8000;
int row = 0;
int col = 0;
int background_color = 113;


void setCursorPosition(int row, int col) {
    int position = row * 80 + col; // Assuming 80 columns

    // Send command byte to VGA registers
    outb(0x3D4, 0x0F); // VGA control register: set low cursor byte
    outb(0x3D5, (unsigned char)(position & 0xFF)); // Low byte

    outb(0x3D4, 0x0E); // VGA control register: set high cursor byte
    outb(0x3D5, (unsigned char)((position >> 8) & 0xFF)); // High byte
}

// calculates the vga text-mode address
int get_address(int row,int column){
   return VID_MEM + 2 * (row * 80 + column);
}

void printf ( char *string ,...)
{
    va_list args;
    int i;
    char *str;
	va_start(args, string);

    while( *string != '\0')
    {
        if (*string == '\n'){
            row += 1;
            col = 0;
            video = (char*)get_address(row,col);
            string +=2;
        }else if (*string == '%'){
            switch (*(string+1))
            {
                char string_num[20];
                case 'd':
                    i = va_arg(args, int);
                    intToString(i,string_num);
                    puts(row,col,string_num,background_color);
                    col +=strlen(string_num);
                    string +=2;
                    break;
                case 'x':
                    i = va_arg(args, int);
                    intToHex(i,string_num);
                    puts(row,col,string_num,background_color);
                    col +=strlen(string_num);
                    string +=2;
                    break;
                case 'c':
                    str = va_arg(args, char*);
                    puts(row,col,str,background_color);
                    col +=strlen(str);
                    string +=2;
                    break;
                default:
                    break;
            }
        }
        else{
            video = (char*)get_address(row,col);
            *video++ = *string++;
            *video++ = background_color;
            col += 1;
        }
    }

    if(row + 1 > 21){
        shiftScreenUp(2);
        row -= 2;
    }
    va_end(args);
}

void vprintf ( char *string ,va_list args)
{
    int i;
    char* str;

    while( *string != '\0')
    {
        if (*string == '\n'){
            row += 1;
            col = 0;
            video = (char*)get_address(row,col);
            string +=2;
        }else if (*string == '%'){
            switch (*(string+1))
            {
                char string_num[20];
                case 'd':
                    i = va_arg(args, int);
                    intToString(i,string_num);
                    puts(row,col,string_num,background_color);
                    col +=strlen(string_num);
                    string +=2;
                    break;
                case 'x':
                    i = va_arg(args, int);
                    intToHex(i,string_num);
                    puts(row,col,string_num,background_color);
                    col +=strlen(string_num);
                    string +=2;
                    break;
                case 'c':
                    str = va_arg(args, char*);
                    puts(row,col,str,background_color);
                    col +=strlen(str);
                    string +=2;
                    break;
                default:
                    break;
            }
        }
        else{
            video = (char*)get_address(row,col);
            *video++ = *string++;
            *video++ = background_color;
            col += 1;
        }
    }

    if(row + 1 > 21){
        shiftScreenUp(2);
        row -= 2;
    }
    //va_end(args);
}

void sprintf(int row_n,int col_n,char* string,...){
    // keep the previous row col location
    int prev_row = row_n;
    int prev_col = col_n;

    row = row_n;
    col = col_n;

    va_list args;
    va_start(args, string);
    vprintf(string, args);
    va_end(args);

    row = prev_row;
    col = prev_col;

}

void putchar(int row,int col,char chr,int colour){
    volatile char *video = (volatile char*)0xB8000;
    video = (char*)get_address(row,col);
    *video++ = chr;
    *video++ = colour;
}

void puts(int row,int col,unsigned char *chr,int colour){
    volatile char *video = (volatile char*)0xB8000;
    video = (char*)get_address(row,col);
    while (*chr !=0)
    {
        *video++ = *chr++;
        *video++ = colour;

    }

}
void clearScreen() {
    // Assuming video is a pointer to the video memory
    char *video = (char *)0xB8000; // Modify this according to your video memory address

    // Fill the screen with blank spaces
    for (int i = 0; i < (24 * 80 * 2); i += 2) {
        video[i] = 0; // Write a space character
        video[i + 1] = background_color; // Set the attribute byte to 0 (assuming default color)
    }
}

void fill_screen() {
    // Assuming video is a pointer to the video memory
    char *video = (char *)0xB8000; // Modify this according to your video memory address

    // Fill the screen with blank spaces
    for (int i = 0; i < (24 * 80 * 2); i += 2) {
        //video[i] = 0; // Write a space character
        video[i + 1] = background_color; // Set the attribute byte to 0 (assuming default color)
        
    }
}

// the 23 was 24 revert if some bug happens
void shiftScreenUp(int times) {

    char *video = (char *)0xB8000; // Modify this according to your video memory address

    for (int time = 1; time <= times; time++)
    {
        for (int i = 0; i < (24 * 80 * 2) - (80 * 2); ++i) {
            video[i] = video[i + 160]; // Shifts the content up by one row (80 columns * 2 bytes per character)
        }

        // Clear the last row to prevent remnants
        for (int i = (24 * 80 * 2) - (80 * 2); i < (24 * 80 * 2); i+=2) {
            video[i] = 0; // Clearing the last row
        }
    }
}