#ifndef KEYBOARD_H
#define KEYBOARD_H

typedef struct {
    char* command;
    char* argument;
} CommandArguments;

typedef struct {
    const char* command;
    void (*action)( CommandArguments* args);
} CommandMapping;

void executor(char* full_command);
void handle_keyboard();
void info(CommandArguments* args);
void clear();
void setcolor(CommandArguments* args);
void count(CommandArguments* args);

extern char *linefeed;
#endif