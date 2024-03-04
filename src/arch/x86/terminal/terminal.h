#ifndef TERMINAL_H
#define TERMINAL_H

typedef struct {
    char* command;
    char* argument;
} CommandArguments;

typedef struct {
    const char* command;
    void (*action)( CommandArguments* args);
} CommandMapping;

void executor(char* full_command);

void terminal(char keyPressed);
void prepare_terminal();

void info(CommandArguments* args);
void clear();
void setcolor(CommandArguments* args);
void count(CommandArguments* args);

extern char *linefeed;
extern int current_time;
extern char *welcome_msg;

#endif