#ifndef STRING_H
#define STRING_H

void reverse(char* str, int length);
void intToString(int num, unsigned char* buffer);
void add_to_string(unsigned char* source,unsigned char* destination,int* size);
void add_char_to_string(char character, char* destination,int* size, int max_size);
void clear_buffer(char* destination, int size);
int str_cmpr(char* str1,const char* str2);
void str_cpy(char* from , char* to);
int strlen(char* str);
char* fill_string(char character,int number);
void split_string(char* string,const char splitter,char** out);
void shift_string_right(char* string,int size);
void shift_string_left(char* string, int size);
int stringToInt(const char* str);

#endif
