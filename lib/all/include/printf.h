/*
** EPITECH PROJECT, 2022
** printf.h
** File description:
** Printf
*/

#ifndef PRINTF_H
    #define PRINTF_H
    #include <stdarg.h>
    #include <stddef.h>
    #include "my.h"
    #define NOT_A_FORMAT 99999

typedef union doublebytes {
    double d;
    unsigned char bytes[8];
}doubleb_t;

typedef struct flags {
    const char flag;
    const int (*func)();
    const int (*pfunc)();
}flags_t;


int my_put_double(va_list valist, char *ptr);

int my_put_double_do(double d, int dec);

int recursive_div_db(double nbr, int base, const char *str);

int my_putdouble_base(double nbr, char *ptr);

int my_putstrlen(va_list valist, char *ptr);

int my_showstr_oct(va_list valist, char *ptr);

int my_pc(va_list valist, char *ptr);

int my_putstr_do(char *str);

int my_putstr(va_list valist, char *ptr);

int my_put_nbr(va_list valist, char *ptr);

int my_put_nbr_do(int n);

int my_putnbr_base(va_list valist, char *ptr);

int my_put_percent(va_list valist, char *ptr);

int recursive_div_unsign(unsigned long int nbr, int base, char *str);

int my_isnumeric(char c);

long int my_getnbr(char const *str);

int my_put_double_prec(va_list valist, int precision, char *ptr);

int process_int(int val, int i);

int get_sign(int i, int sign);

double my_power_it(double n, int p);

double power_neg(double n, int p);

int my_putstr_prec(va_list valist, int prec, char *str);

int my_isalpha_f(char c);

int get_precision(va_list valist, char *ptr);

int my_getnbr_len_fs(const char *str);

int put_pointer(va_list va_list, char *ptr);

int my_getnbr_len(int nbr);

double rounding_d(double f, int dec);

int my_put_double_hex(va_list valist, char *ptr);

int my_unsign_putnbr_base_do(unsigned long int nbr, char *str);

int my_putdouble_sci(va_list valist, char *ptr);

int my_putdouble_sciprec(va_list valist, int precision, char *ptr);

int mpd_sci_do(double d, int dec, char cexp);

int get_exp(double d);

int put_exp(int exp);

int my_ustrlen(unsigned char const *str);

int my_put_double_hex(va_list valist, char *ptr);

int my_putdouble_hex_prec(va_list valist, int precision, char *ptr);

int my_put_double_hex_do(double d, int dec, char cexp);

int print_mantissa(unsigned char* bytes, int dec, char *base);

char *set_str(char *base, char *news);

int is_pow2(unsigned char *bytes);

int is_next_null(unsigned char *bytes, int half, int limit);

int print_exp(int exp, char cexp);

int my_showstr_oct_do(char *str, int ltp);

int my_showstr_oct_prec(va_list valist, int precision, char *ptr);

int my_unsigned_put_nbr_do(unsigned long int n);

int my_shortest(va_list ap, char *ptr);

int my_shortestp(va_list ap, char *ptr, int precision);

int my_put_shortest_double_do(double d, int dec);

int mpsd_sci_do(double d, int dec, char cexp);

int my_get_only_nbr(char const *str);

extern const int nbpflags;
extern const int nbflags;
extern const flags_t all_flags[22];
#endif
