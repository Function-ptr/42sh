/*
** EPITECH PROJECT, 2022
** my_showstr_oct.c
** File description:
** my_showstr_oct
*/

#include <stdarg.h>
#include "include/printf.h"

int my_showstr_oct_do(char *str, int ltp)
{
    int len = 0;
    for (int i = 0; str[i] != '\0' && ltp != 0; i++) {
        int printed = 0;
        if (str[i] < 8) {
            len += my_putstr_do("\\00");
            len += my_unsign_putnbr_base_do(str[i], "01234567");
            printed = 1;
        }
        if (str[i] < 32 && printed == 0) {
            len += my_putstr_do("\\0");
            len += my_unsign_putnbr_base_do(str[i], "01234567");
            printed = 1;
        }
        if (printed == 0) {
            len += my_putchar(str[i]);
        }
    }
    return (len);
}

int my_showstr_oct(va_list valist, char *ptr)
{
    char *str = va_arg(valist, char *);
    int len = my_showstr_oct_do(str, -1);
    return (len);
}

int my_showstr_oct_prec(va_list valist, int precision, char *ptr)
{
    char *str = va_arg(valist, char *);
    int len = my_showstr_oct_do(str, precision);
    return (len);
}
