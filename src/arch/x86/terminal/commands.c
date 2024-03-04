#include "terminal.h"
#include "std/stdout.h"
#include "utils/string.h"
#include "utils/controller.h"

void info(CommandArguments* args){
    printf("here are all the commands:");
    printf("\n setcolor {color_int} - sets the terminal color");
    printf("\n clear - clears the screen");
}

void clear(CommandArguments* args){
    row = 0;
    col = 0;
    clearScreen();
    setCursorPosition(20, 20);
}

void setcolor(CommandArguments* args){
    int color = stringToInt(args->argument);
    // puts(20,40,split_command[1],6);
    if (strlen(args->argument) == 2){
        background_color = color;
        printf("ok setting color \n\0");
        fill_screen();

    }else{
        printf("int should be only 2 digit \n\0");
    }
}

void count( CommandArguments* args){

    int count_num = stringToInt(args->argument);

    for (int i = 0; i < count_num; i++)
    {
        printf("%d\n\0",i);
    }
}
