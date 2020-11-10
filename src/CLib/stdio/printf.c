#include "stdio.h"
/*
The function prints a simple string and returns if the string was printed properly
const char* data - string to print
size_t length - length of string
*/
static bool print(const char *data, size_t length)
{
    const unsigned char *bytes = (const unsigned char *)data; //assign string into bytes array of Ascii values
    for (size_t i = 0; i < length; i++) //print each byte with putchar function
        if (putchar(bytes[i]) == EOF)
            return false;
    return true;
}

/*
The function will print a string with option to other values(integer, float, char, string). 
returns how many bytes where written.
const char* restrict format - string to print
... - option to enter several parameters such as integer (%d), float (%f), char (%c), string (%s).
*/
int printf(const char *restrict format, ...)
{
    va_list parameters; //list of parameters
    va_start(parameters, format);

    int written = 0; //initialize 0 written bytes

    while (*format != '\0')
    {
        size_t maxrem = INT_MAX - written;

        if (format[0] != '%' || format[1] == '%') //check for entered parameters with %d
        {
            if (format[0] == '%')
                format++;
            size_t amount = 1;
            while (format[amount] && format[amount] != '%')
                amount++;
            if (maxrem < amount)
            {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(format, amount))
                return -1;
            format += amount;
            written += amount;
            continue;
        }

        const char *format_begun_at = format++;

        if (*format == 'c')
        {
            format++;
            char c = (char)va_arg(parameters, int /* char promotes to int */);
            if (!maxrem)
            {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(&c, sizeof(c)))
                return -1;
            written++;
        }
        if (*format == 'd')
        {
            //FIXME - implement in a better way
            format++;
            int d = (char)va_arg(parameters, int /* char promotes to int */);
            char tmp[32] = {0};
            if (!maxrem)
            {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            itoa(d, tmp, 10);
            if (!print(tmp, strlen(tmp)))
                return -1;
            written++;
        }
        else if (*format == 's')
        {
            format++;
            const char *str = va_arg(parameters, const char *);
            size_t len = strlen(str);
            if (maxrem < len)
            {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(str, len))
                return -1;
            written += len;
        }
        else
        {
            format = format_begun_at;
            size_t len = strlen(format);
            if (maxrem < len)
            {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(format, len))
                return -1;
            written += len;
            format += len;
        }
    }

    va_end(parameters);
    return written;
}
