/*
** EPITECH PROJECT, 2022
** my_putstrlen.c
** File description:
** my_putstrlen
*/

#include <stdarg.h>
#include "include/printf.h"

int my_putstrlen(va_list valist, char *ptr)
{
    char *str = va_arg(valist, char *);
    int len;
    int res;
    for (len = 0; str[len] != '\0'; len++) {
    }
    res = my_put_nbr_do(len);
    return (res);
}
