/*
** EPITECH PROJECT, 2022
** my_put_double_hex.c
** File description:
** my_put_double_hex for the -a and -A flags
*/

#include "include/printf.h"

int is_next_null(unsigned char *bytes, int half, int limit)
{
    if (half) {
        if (bytes[limit] % 16 != 0)
            return (0);
        limit--;
    }
    for (int i = limit; i >= 0; i--) {
        if (bytes[i] != 0)
            return (0);
    }
    return (1);
}

int is_pow2(unsigned char *bytes)
{
    if (bytes[6] % 16 != 0)
        return (0);
    for (int i = 0; i < 6; i++) {
        if (bytes[i] != 0)
            return (0);
    }
    return (1);
}

int print_mantissa(unsigned char *bytes, int dec, char *base)
{
    int len = 0;
    if (is_pow2(bytes))
        return (0);
    len += my_putchar('.');
    len += my_unsign_putnbr_base_do(bytes[6] % 16, base);
    dec--;
    for (int i = 5; i >= 0 && dec != 0 && !is_next_null(bytes, 0, i); i--,
        dec--) {
        unsigned char tmp = bytes[i];
        len += my_unsign_putnbr_base_do((tmp >> 4) % 16, base);
        dec--;
        if (dec == 0 || is_next_null(bytes, 1, i))
            return (len);
        len += my_unsign_putnbr_base_do(tmp % 16, base);
    }
    return (len);
}

int print_exp(int exp, char cexp)
{
    int len = 0;
    char sexp = '+';
    len += my_putchar(cexp);
    if (exp < 0) {
        sexp = '-';
        exp = -exp;
    }
    len += my_putchar(sexp);
    len += my_put_nbr_do(exp);
    return (len);
}

int my_put_double_hex_do(double d, int dec, char cexp)
{
    doubleb_t db;
    db.d = d;
    int len = 0;
    unsigned char *bytes = db.bytes;
    char *base = "0123456789abcdef", *baseindic = "0x";
    if (cexp == 'P') {
        base = set_str(base, "0123456789ABCDEF");
        baseindic = set_str(baseindic, "0X");
    }
    char intsci = (d == 0.0) ? ('0') : ('1');
    if (bytes[7] >= 128) {
        len += my_putchar('-');
        bytes[7] -= 128;
    }
    int exp = (((bytes[7] << 8) + bytes[6]) >> 4) - 1023;
    if ((((bytes[7] << 8) + bytes[6]) >> 4) == 0)
        exp = 0;
    len += (my_putstr_do(baseindic) + my_putchar(intsci));
    len += (print_mantissa(bytes, dec, base) + print_exp(exp, cexp));
    return (len);
}
