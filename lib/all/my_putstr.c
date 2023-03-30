/*
** EPITECH PROJECT, 2022
** my_putstr.c
** File description:
** my_putstr
*/

#include <stdarg.h>
#include "include/printf.h"

int my_putstr(va_list valist, char *ptr)
{
    char *str = va_arg(valist, char *);
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        my_putchar(str[i]);
    }
    return (i);
}

int my_putstr_do(char *str)
{
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        my_putchar(str[i]);
    }
    return (i);
}

int my_putstr_prec(va_list valist, int prec, char *ptr)
{
    char *str = va_arg(valist, char *);
    int i;
    for (i = 0; str[i] != '\0' && i < prec; i++) {
        my_putchar(str[i]);
    }
    return (i);
}
