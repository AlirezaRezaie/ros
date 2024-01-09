#ifndef STRING_H
#define STRING_H

void reverse(char* str, int length);
void intToString(int num, unsigned char* buffer);
void add_to_string(unsigned char* source,unsigned char* destination,int* size);
void add_char_to_string(char character, char* destination,int* size, int max_size);
int str_cmpr(char* str1,const char* str2);

#endif
