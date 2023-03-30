/*
** EPITECH PROJECT, 2022
** my_shortest.c
** File description:
** do flag g/G of my_printf
*/

#include <stdarg.h>
#include "include/printf.h"

int my_shortest(va_list ap, char *ptr)
{
    double d = va_arg(ap, double);
    int exp = get_exp(d), precision = 6;
    if (ptr[0] == 'G') {
        if (precision > exp && exp >= -4)
            return (my_put_shortest_double_do(d, precision - 1));
        else
            return (mpsd_sci_do(d, precision - 1 - exp, 'E'));
    } else {
        if (precision > exp && exp >= -4)
            return (my_put_shortest_double_do(d, precision - 1));
        else
            return (mpsd_sci_do(d, precision - 1 - exp, 'e'));
    }
}

int my_shortestp(va_list ap, char *ptr, int precision)
{
    double d = va_arg(ap, double);
    int exp = get_exp(d);
    if (precision <= 0)
        precision = 1;
    if (ptr[0] == 'G') {
        if (precision > exp && exp >= -4)
            return (mpsd_sci_do(d, precision - 1 - exp, 'E'));
        else
            return (my_put_shortest_double_do(d, precision - 1));
    } else {
        if (precision > exp && exp >= -4)
            return (mpsd_sci_do(d, precision - 1 - exp, 'e'));
        else
            return (my_put_shortest_double_do(d, precision - 1));
    }
}
