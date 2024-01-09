
#include "stdout.h"

volatile char *video = (volatile char*)0xB8000;
int row = 0;
int col = 0;

// calculates the vga text-mode address
int get_address(int row,int column){
   return VID_MEM + 2 * (row * 80 + column);
}

// writes string to the video memory (.n) is newline
void print( int colour,  char *string )
{
    while( *string != 0)
    {
        if(*string  == '.' && *(string + 1) == 'n')
        {
            row += 1;
            col = 0;
            video = (char*)get_address(row,col);
            string +=2;
            continue;
        }
        else{
            video = (char*)get_address(row,col);
            *video++ = *string++;
            *video++ = colour;
            col += 1;
        }
    }
}
void sprint( int colour,  char *string )
{
    while( *string != '.')
    {
        if(*string  == '.' && *(string + 1) == 'n')
        {
            row += 1;
            col = 0;
            video = (char*)get_address(row,col);
            string +=2;
            continue;
        }
        else{
            video = (char*)get_address(row,col);
            *video++ = *string++;
            *video++ = colour;
            col += 1;
        }
    }
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
    for (int i = 0; i < (25 * 80 * 2); i += 2) {
        video[i] = 0; // Write a space character
        //video[i + 1] = 0; // Set the attribute byte to 0 (assuming default color)
    }
}

void shiftScreenUp() {
    char *video = (char *)0xB8000; // Modify this according to your video memory address
    for (int i = 0; i < (24 * 80 * 2) - (80 * 2); ++i) {
        video[i] = video[i + 160]; // Shifts the content up by one row (80 columns * 2 bytes per character)
    }

    // Clear the last row to prevent remnants
    for (int i = (24 * 80 * 2) - (80 * 2); i < (24 * 80 * 2); i+=2) {
        video[i] = 0; // Clearing the last row
    }

}