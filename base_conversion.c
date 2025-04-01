#include "base_conversion.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0

const char DIGITS_CHAR[] = {
    '0',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    'A',
    'B',
    'C',
    'D',
    'E',
    'F'
};

unsigned int get_dec_by_char(const char digit) {
    unsigned int res = 0;
    switch (digit) {
    // Default digits
    case '0': res = 0; break;
    case '1': res = 1; break;
    case '2': res = 2; break;
    case '3': res = 3; break;
    case '4': res = 4; break;
    case '5': res = 5; break;
    case '6': res = 6; break;
    case '7': res = 7; break;
    case '8': res = 8; break;
    case '9': res = 9; break;

        // Upper case
    case 'A': res = 10; break;
    case 'B': res = 11; break;
    case 'C': res = 12; break;
    case 'D': res = 13; break;
    case 'E': res = 14; break;
    case 'F': res = 15; break;

    // Lower case
    case 'a': res = 10; break;
    case 'b': res = 11; break;
    case 'c': res = 12; break;
    case 'd': res = 13; break;
    case 'e': res = 14; break;
    case 'f': res = 15; break;

    default: res = 0; break;
    }
    return res;
}


int fits_in_32_bits(const char* str, unsigned int base) {
    if (base < 2 || base > 16) return 0;

    int is_negative = 0;
    const char* num_start = str;

    if (*num_start == '-') {
        if (base != 10) return 0;
        is_negative = 1;
        num_start++;
    } else if (*num_start == '+') {
        num_start++;
    }

    if (*num_start == '\0') return 0;

    uint32_t max_val;
    if (base == 10) {
        if (is_negative) {
            max_val = 2147483648U;
        } else {
            max_val = INT32_MAX;
        }
    } else {
        max_val = UINT32_MAX;
    }

    uint32_t value = 0;
    uint32_t max_div_base = max_val / base;

    for (const char* p = num_start; *p != '\0'; p++) {
        if (*p == '-' && base != 10) {
            is_negative = 1;
            continue;
        }

        int digit;
        if (isdigit(*p)) {
            digit = *p - '0';
        } else if (isupper(*p)) {
            digit = *p - 'A' + 10;
        } else if (islower(*p)) {
            digit = *p - 'a' + 10;
        } else {
            return 0;  // Недопустимый символ
        }

        if (digit >= base) return 0;

        if (value > max_div_base) return 0;
        value *= base;

        if (value > max_val - digit) return 0;
        value += digit;
    }

    if (is_negative && base != 10) {
        if (value > 2147483648U) return 0;
    }

    return 1;
}

int validate_base(const char *str, const unsigned int base) {
    for (size_t i = 0; i < strlen(str); i++) {
        if (base == 10 && str[0] == '-'){
            continue;
        }
        if (get_dec_by_char(str[i]) >= base) {
            return FALSE;
        }
    }
    return TRUE;
}

void reverse_str(char *start, char *end) {
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

char *dec_to_any(const int num, const unsigned int base) {
    if (base > 16 || base < 2) {
        return NULL;
    }

    char *str = (char *)malloc(sizeof(char) * 33);
    str[0] = '\0';

    int coef = (num < 0 && base == 10) ? -1 : 1;

    int cpy_num = coef * num;
    do {
        char digit[2];
        digit[0] = DIGITS_CHAR[cpy_num % base];
        digit[1] = '\0';

        strcat(str, digit);
        cpy_num /= base;
    } while (cpy_num);

    if (coef == -1) {
        strcat(str, "-\0");
    }

    reverse_str(str, str + strlen(str) - 1);

    return str;
}

int any_to_dec(const char *str, const unsigned int base) {
    int result = 0;

    if (validate_base(str, base)) {
        size_t length = strlen(str);

        for (size_t i = length; i != 0; i--) {
            result += get_dec_by_char(str[length - i]) * pow(base, i - 1);
        }
    }

    return result;
}

int str_to_int(const char *str) {
    int num = 0;

    if (validate_base(str, 10)) {
        const size_t length = strlen(str);
        for (size_t i = 0; i < length; i++) {
            if (str[i] != '-') {
                unsigned int digit = (int)str[i] - '0';
                num += (int)(digit * pow(10, length - i - 1));
            }
        }

        if (str[0] == '-') {
            num = (-1) * num;
        }
    }
    return num;
}