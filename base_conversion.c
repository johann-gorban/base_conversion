#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "base_conversion.h"

char *reverse_str(const char *str) {
    if (!str)
        return NULL;

    size_t length = strlen(str);
    char *reversed_str = (char *)calloc(length, sizeof(char));

    for (size_t i = length; i != 0; i--) {
        reversed_str[length - i] = str[i - 1];
    }

    return reversed_str;
}

char *dec_to_any(const unsigned long num, const unsigned int base) {
    if (base > 16 || base < 2)
        return NULL;

    char *str = (char *)malloc(sizeof(char));
    str[0] = '\0';

    unsigned long cpy_num = num;
    do {
        char digit[2];
        digit[0] = DIGITS_CHAR[cpy_num % base];
        digit[1] = '\0';

        strcat(str, digit);
        cpy_num /= base;
    } while (cpy_num);
    
    return reverse_str(str);
}

