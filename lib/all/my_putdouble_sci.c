/*
** EPITECH PROJECT, 2022
** my_putdouble_sci.c
** File description:
** put double in base 10 scientific notation
*/

#include <stdarg.h>
#include "include/printf.h"

int put_exp(int exp)
{
    int len = 0;
    if (exp < 10) {
        my_putchar('0');
        my_put_nbr_do(exp);
        return (2);
    }
    len += my_put_nbr_do(exp);
    return (len);
}

int get_exp(double d)
{
    if (d < 0)
        d = -d;
    int exp = 0;
    if (d >= 10)
        return (my_getnbr_len((int)(d / 10)));
    if (d < 1 && d > 0) {
        for (; d < 1; exp--, d *= 10) {
        }
    }
    return (exp);
}

int mpd_sci_do(double d, int dec, char cexp)
{
    doubleb_t db;
    db.d = d;
    if (db.bytes[7] >= 128) {
        d = -d;
        my_putchar('-');
    }
    int exp = get_exp(d), len = 0, esign = 43;
    d = rounding_d(d, dec - exp);
    if (exp > 0)
        d *= power_neg((double)10, exp);
    if (exp < 0)
        d *= my_power_it((double)10, -exp);
    d = rounding_d(d, dec);
    len += (my_put_double_do(d, dec) + my_putchar(cexp));
    if (exp < 0) {
        esign += 2;
        exp = -exp;
    }
    len += (my_putchar(esign) + put_exp(exp));
    return (len);
}

int my_putdouble_sci(va_list valist, char *ptr)
{
    char cexp = 'e';
    if (ptr[0] == 'E')
        cexp = 'E';
    double val = va_arg(valist, double);
    int len = 0;
    len += mpd_sci_do(val, 6, cexp);
    return (len);
}

int my_putdouble_sciprec(va_list valist, int precision, char *ptr)
{
    char cexp = 'e';
    if (ptr[0] == 'E')
        cexp = 'E';
    double val = va_arg(valist, double);
    int len = 0;
    len += mpd_sci_do(val, precision, cexp);
    return (len);
}
