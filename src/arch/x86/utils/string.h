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

void intToString(int num, char* buffer) {
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
