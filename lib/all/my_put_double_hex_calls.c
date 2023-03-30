/*
** EPITECH PROJECT, 2022
** my_putdouble_hex_calls.c
** File description:
** funcs to call my_put_double_hex
*/

#include "include/printf.h"
#include <stdarg.h>

int my_put_double_hex(va_list valist, char *ptr)
{
    double d = va_arg(valist, double);
    char cexp = 'p';
    if (ptr[0] == 'A')
        cexp = 'P';
    int r = my_put_double_hex_do(d, 0, cexp);
    return (r);
}

int my_putdouble_hex_prec(va_list valist, int precision, char *ptr)
{
    double d = va_arg(valist, double);
    char cexp = 'p';
    if (ptr[0] == 'A')
        cexp = 'P';
    int r = my_put_double_hex_do(d, precision, cexp);
    return (r);
}
