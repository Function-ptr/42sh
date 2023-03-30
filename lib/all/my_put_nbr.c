/*
** EPITECH PROJECT, 2022
** my_put_nbr.c
** File description:
** my_put_nbr
*/

#include <stdarg.h>
#include "include/printf.h"

int my_put_lnbr_do(long int n)
{
    int buffer = 0;
    int nb_printed = 0;
    if (n <= -9223372036854775807) {
        n = n + 1;
        buffer = 1;
    }
    if (n < 0) {
        my_putchar(45);
        n = -n;
    }
    if (n >= 10) {
        nb_printed = my_put_nbr_do(n / 10);
    }
    my_putchar(n % 10 + 48 + buffer);
    return (nb_printed + 1);
}

int my_unsigned_put_nbr_do(unsigned long int n)
{
    int nb_printed = 0;
    if (n >= 10) {
        nb_printed = my_unsigned_put_nbr_do(n / 10);
    }
    my_putchar(n % 10 + 48);
    return (nb_printed + 1);
}

int my_put_lnbr(va_list valist, char *ptr)
{
    long int v = va_arg(valist, long int);
    if (ptr[0] == 'u')
        return (my_unsigned_put_nbr_do((unsigned long int)v));
    return (my_put_nbr_do(v));
}

int my_put_nbr_do(int n)
{
    int buffer = 0;
    int nb_printed = 0;
    if (n <= -2147483648) {
        n = n + 1;
        buffer = 1;
    }
    if (n < 0) {
        my_putchar(45);
        n = -n;
    }
    if (n >= 10) {
        nb_printed = my_put_nbr_do(n / 10);
    }
    my_putchar(n % 10 + 48 + buffer);
    return (nb_printed + 1);
}

int my_put_nbr(va_list valist, char *ptr)
{
    return (my_put_nbr_do(va_arg(valist, int)));
}
