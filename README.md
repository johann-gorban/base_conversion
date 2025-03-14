# Fucntions for numbers conversion

List of functions
- char *dec_to_any(const unsigned long num, const unsigned int base)
- unsigned long any_to_dec(const char *str, const unsigned int base) # in development

You can yous any number smaller than 16 and greater than 0 as base. If something went wrong, functions return NULL

## How to use it
To convert your number from binary to hexidecimal system:
```
unsigned long dec_num = any_to_dec(your_num_as_str, 2);
const char *hex_num = dec_to_any(dec_num, 16);
```


## Future updates
- negative numbers support [done]
