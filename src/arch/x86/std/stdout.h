
#define VID_MEM 0xb8000

// printing.h
#ifndef STDOUT_H
#define STDOUT_H

extern volatile char *video;
extern int row;
extern int col;
extern int background_color;

void print(int colour, char *string);
void sprint( int colour, char *string);
void puts(int row, int col,unsigned char *chr,int colour);

void clearScreen();
void fill_screen();
void shiftScreenUp();

#endif
