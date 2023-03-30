/*
** EPITECH PROJECT, 2022
** my_put_double.c
** File description:
** my_put_double
*/

#include "include/printf.h"
#include <stdarg.h>

double rounding_d(double f, int dec)
{
    double pn = power_neg((double)10, dec);
    double pp = my_power_it((double)10, dec);
    if ((int)(f * (pp * 10)) % 10 > 4)
        f += 5 * (pn / 10);
    return (f);
}

int my_put_double_do(double d, int dec)
{
    doubleb_t db;
    db.d = d;
    if (db.bytes[7] >= 128) {
        d = -d;
        my_putchar('-');
    }
    d = rounding_d(d, dec);
    int len;
    int tmp = (int)d;
    len = my_put_nbr_do(tmp);
    d -= tmp;
    int prec = dec;
    len += my_putchar('.');
    for (int i = 0; i < prec; i++, dec--) {
        d = rounding_d(10 * d, dec);
        tmp = (int)d;
        len += my_put_nbr_do(tmp);
        d -= tmp;
    }
    return (len);
}

int my_put_double(va_list valist, char *ptr)
{
    double d = va_arg(valist, double);
    int res = my_put_double_do(d, 6);
    return (res);
}

int my_put_double_prec(va_list valist, int precision, char *ptr)
{
    double d = va_arg(valist, double);
    int res = my_put_double_do(d, precision);
    return (res);
}
