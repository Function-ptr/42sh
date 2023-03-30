/*
** EPITECH PROJECT, 2022
** my_putpointer.c
** File description:
** my_put_pointer
*/

#include <stdarg.h>
#include "include/printf.h"

int put_pointer(va_list va_list, char *ptr)
{
    long int p = (long int) va_arg(va_list, void*);
    int res = 0;
    res += my_putstr_do("0x");
    res += my_unsign_putnbr_base_do(p, "0123456789abcdef");
    return (res);
}
