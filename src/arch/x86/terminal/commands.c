#include "terminal.h"
#include "std/stdout.h"
#include "utils/string.h"
#include "utils/controller.h"

void info(CommandArguments* args){
    print(15,"here are all the commands: .n");
    print(15,"setcolor {color_int} - sets the terminal color.n");
    print(15,"clear - clears the screen.n");
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
        print(2,"ok setting color.n");
    }else{
        print(2,"int should be only 2 digit .n");
    }
}

void count( CommandArguments* args){    
    print(3, " .n ");

    int count_num = stringToInt(args->argument);

    for (int i = 0; i < count_num; i++)
    {
        char* num;
        intToString(i,num);
        //print(15,"counting: ");
        print(15,num);
        print(3,".n");
    }
}
