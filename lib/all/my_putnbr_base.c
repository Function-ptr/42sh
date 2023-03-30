/*
** EPITECH PROJECT, 2022
** my_putnbr_base.c
** File description:
** my_putnbr_base
*/

#include "include/printf.h"
#include <stdarg.h>

int recursive_div_unsign(unsigned long int nbr, int base, char *str)
{
    int r = 0;
    if (nbr == 0)
        return (0);
    r = recursive_div_unsign(nbr / base, base, str);
    my_putchar(str[nbr % base]);
    return (r + 1);
}

int my_unsign_putnbr_base_do(unsigned long int nbr, char *str)
{
    int base = my_strlen(str);
    int r;
    if (base < 2)
        return (0);
    if (nbr == 0) {
        my_putchar('0');
        return (1);
    }
    r = recursive_div_unsign(nbr, base, str);
    return (r);
}

int my_putnbr_base(va_list valist, char *ptr)
{
    unsigned int nbr = va_arg(valist, unsigned int);
    if (ptr[0] == 'x' || ptr[0] == 'X') {
        if (ptr[0] == 'X')
            return (my_unsign_putnbr_base_do(nbr, "0123456789ABCDEF"));
        return (my_unsign_putnbr_base_do(nbr, "0123456789abcdef"));
    }
    if (ptr[0] == 'o') {
        return (my_unsign_putnbr_base_do(nbr, "01234567"));
    }
    if (ptr[0] == 'b')
        return (my_unsign_putnbr_base_do(nbr, "01"));
    return (0);
}
