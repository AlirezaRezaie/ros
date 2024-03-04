
#define VID_MEM 0xb8000
#define VID_SIZE 25*80*2

// printing.h
#ifndef STDOUT_H
#define STDOUT_H

extern volatile char *video;
extern int row;
extern int col;
extern int background_color;

void printf ( char *string ,...);
void sprintf(int row,int col,char* string,...);
void puts(int row, int col,unsigned char *chr,int colour);
void setCursorPosition(int row, int col);

void clearScreen();
void fill_screen();
void shiftScreenUp(int times);

#endif
