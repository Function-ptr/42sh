/*
** EPITECH PROJECT, 2022
** get_precision.c
** File description:
** get_precision
*/

#include "include/printf.h"
#include <stdarg.h>

int my_isalpha_f(char c)
{
    if ((c > 64 && c < 91 && c != 72 && c != 76) ||
        (c > 96 && c < 123 && c != 104 && c != 108))
        return (1);
    return (0);
}

int precision_flags_fs(char *ptr)
{
    int nb_p = 0;
    nb_p += my_putchar('%');
    for (int i = 0; !my_isalpha_f(ptr[i]); i++) {
        nb_p += my_putchar(ptr[i]);
    }
    return (nb_p);
}

int get_precision(va_list valist, char *ptr)
{
    const int nbpflags = 9;
    unsigned int prec = 0;
    int nb_printed = 0, i, j;
    if (ptr[1] == '*')
        prec = va_arg(valist, unsigned int);
    else
        prec = my_getnbr((const char *)ptr);
    prec = (prec == 0) ? (1) : (prec);
    for (i = 0; !my_isalpha_f(ptr[i]); i++) {
    }
    for (j = 0; ptr[i] != all_flags[j].flag && all_flags[j].flag != '\0'; j++) {
    }
    if (j != nbpflags - 1)
        nb_printed += all_flags[j].pfunc(valist, prec, &ptr[i]);
    else
        nb_printed += precision_flags_fs(ptr);
    return (nb_printed);
}
