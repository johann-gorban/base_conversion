# Fucntions for numbers conversion

List of functions

### Encoding
```
char *dec_to_any(const int num, const unsigned int base)
```
### Decoding
```
int any_to_dec(const char *str, const unsigned int base)
```

You can yous any number smaller than 16 and greater than 0 as base. If something went wrong, functions return NULL

## How to use it
To convert your number from binary to hexidecimal system:
```
unsigned long dec_num = any_to_dec(your_num_as_str, 2);
const char *hex_num = dec_to_any(dec_num, 16);
```
## Future updates
- negative numbers support [done]
- check how big num is (overflow)
