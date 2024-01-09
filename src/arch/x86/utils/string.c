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