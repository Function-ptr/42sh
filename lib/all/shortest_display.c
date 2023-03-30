/*
** EPITECH PROJECT, 2022
** shortest_display.c
** File description:
** double display funcs for %g
*/

#include <stdarg.h>
#include "include/printf.h"

int rest_is_null(double d, int dec)
{
    int tmp;
    for (; 0 < dec; dec--) {
        d = rounding_d(10 * d, dec);
        tmp = (int)d;
        d -= tmp;
        if (tmp != 0)
            return (0);
    }
    return (1);
}

double show_dec_double(double d, int dec, int *len)
{
    d = rounding_d(10 * d, dec);
    int tmp = (int)d;
    *len += my_put_nbr_do(tmp);
    d -= tmp;
    return (d);
}

int mpsd_sci_do(double d, int dec, char cexp)
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
    len += (my_put_shortest_double_do(d, dec) + my_putchar(cexp));
    if (exp < 0) {
        esign += 2;
        exp = -exp;
    }
    len += (my_putchar(esign) + put_exp(exp));
    return (len);
}

int my_put_shortest_double_do(double d, int dec)
{
    int len = 0, sign = 0;
    doubleb_t db;
    db.d = d;
    if (db.bytes[7] >= 128) {
        d = -d;
        sign = my_putchar('-');
    }
    int tmp = (int)d;
    len += my_put_nbr_do(tmp);
    if (d == tmp || len == dec + 1)
        return (len);
    d = rounding_d(d, dec);
    d -= tmp;
    int prec = dec - len;
    len += my_putchar('.');
    for (int i = 0; i < dec; i++, prec--) {
        d = show_dec_double(d, prec, &len);
        if (rest_is_null(d, prec))
            break;
    } return (len + sign);
}
