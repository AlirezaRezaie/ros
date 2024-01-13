// some utils
void reverse(char* str, int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

void intToString(int num, unsigned char* buffer) {
    int i = 0;
    int isNegative = 0;

    // Handle negative numbers
    if (num < 0) {
        isNegative = 1;
        num = -num;
    }

    // Process individual digits
    while (num != 0) {
        int remainder = num % 10;
        buffer[i++] = remainder + '0';
        num = num / 10;
    }

    // For negative numbers, add '-'
    if (isNegative) {
        buffer[i++] = '-';
    }

    // If number is 0
    if (i == 0) {
        buffer[i++] = '0';
    }

    buffer[i] = '\0'; // Null-terminate the string

    // Reverse the string
    reverse(buffer, i);
}

void add_to_string(unsigned char* source,unsigned char* destination,int* size){
    destination += *size;
    while (*source !=0)
    {
        *destination++ = *source++;
        (*size)++;
    }
}

void add_char_to_string(char character, char* destination, int* size, int max_size) {
    destination[*size] = character;
    (*size) += 1;
    destination[*size] = '\0'; // Ensure null-termination
}

void add_string_by_size(int from_size,int to_size, char* from,char* to){
    // cuts the string from from_size to to_size and put it in to
    int limit = (to_size-from_size);
    for (int i = from_size; i < to_size; i++)
    {
        to[i%limit] = from[i];
    }
    to[limit] = '\0';
}

void str_cpy(char* dest, const char* src) {
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0'; // Null-terminate the destination string
}

int strlen(char* str) {
    int length = 0; // Initialize length to zero

    // Loop until the null terminator is encountered
    while (str[length] != '\0') {
        length++; // Increment the length for each character
    }

    return length;
}

int str_cmpr(const char* str1, const char* str2){
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2){
            return 0;
        }
        str1++;
        str2++;
    }
    
    // Check if both strings have reached the end
    if (*str1 == '\0' && *str2 == '\0') {
        return 1; // Strings are equal
    } else {
        return 0; // Strings are of different lengths
    }
}

char* fill_string(char character,int number){
    char *out;
    for (int i = 0; i < number; i++)
    {
        out[i] = character;
    }
    
    return out;
}

void clear_buffer(char* destination, int size) {
    // Overwrite the buffer content with null characters
    for (int i = 0; i < size; ++i) {
        destination[i] = ' ';
    }
}

void split_string(char* string,const char splitter,char** out){
    int string_index = 0;
    int string_list_index=0;
    int length = strlen(string);
    for (int i = 0; i < length; i++)
    {
        if(string[i] == splitter){
            char part1[i];
            char part2[length-i];


            add_string_by_size(0,i,string,part1);
            add_string_by_size(i,length,string,part2);

            out[0] = part1;
            out[1] = part2;
            break;
        }
    }

}

void shift_string_right(char* string,int size){
    char last_char = string[size - 1];

    for (int i = size - 1; i > 0; i--) {
        string[i] = string[i - 1];
    }
    string[0] = last_char;
}

void shift_string_left(char* string, int size) {
    char first_char = string[0];

    for (int i = 0; i < size - 1; i++) {
        string[i] = string[i + 1];
    }
    string[size - 1] = first_char;
}

int stringToInt(const char* str) {
    if (!str || *str == '\0') {
        // Handle the case when the string is empty
        return 0;
    }

    int result = 0;
    int sign = 1; // 1 for positive, -1 for negative

    // Handle negative sign
    if (*str == '-') {
        sign = -1;
        ++str;
    }

    // Iterate through the string and convert each digit
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        ++str;
    }

    // Apply the sign
    return sign * result;
}