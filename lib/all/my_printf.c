/*
** EPITECH PROJECT, 2022
** my_printf.c
** File description:
** Reproduce the behavior of the printf function
*/

#include "./include/printf.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

const int nbpflags = 10;
const int nbflags = 21;
const flags_t all_flags[22] = {
    {'d', my_put_nbr, NULL},
    {'i', my_put_nbr, NULL},
    {'c', my_pc, NULL},
    {'s', my_putstr, my_putstr_prec},
    {'%', my_put_percent, NULL},
    {'o', my_putnbr_base, NULL},
    {'u', my_put_nbr, NULL},
    {'x', my_putnbr_base, NULL},
    {'X', my_putnbr_base, NULL},
    {'e', my_putdouble_sci, my_putdouble_sciprec},
    {'E', my_putdouble_sci, my_putdouble_sciprec},
    {'f', my_put_double, my_put_double_prec},
    {'F', my_put_double, my_put_double_prec},
    {'g', my_shortest, my_shortestp},
    {'G', my_shortest, my_shortestp},
    {'a', my_put_double_hex, my_putdouble_hex_prec},
    {'A', my_put_double_hex, my_putdouble_hex_prec},
    {'p', put_pointer, NULL},
    {'b', my_putnbr_base, NULL},
    {'S', my_showstr_oct, my_showstr_oct_prec},
    {'.', get_precision, NULL},
    {'\0', NULL, NULL}
};

int pass_multic_form(const char *ptr)
{
    int to_add = 0;
    if (ptr[0] == '%' && ptr[1] == '.') {
        if (ptr[2] == '*')
            return (2);
        to_add = my_getnbr_len_fs(ptr) + 1;
    }
    if (ptr[0] == '%' && (ptr[1] == 'h' || ptr[1] == 'l')) {
        to_add = (ptr[2] == 'h' || ptr[2] == 'l') ? (2) : (1);
    }
    return (to_add);
}

int put_formats(const char *f, int i, va_list valist, int *nb_p)
{
    int curr_flag = -1;
    int j = 0;
    for (; f[i] == 37 && all_flags[j].flag != '\0' &&
    f[i + 1] != all_flags[j].flag; curr_flag++, j++) {
    }
    if (f[i] == 37 && f[i + 1] == all_flags[0].flag)
        curr_flag++;
    if (f[i] == 37 && f[i + 1] == 'n')
        *(va_arg(valist, int*)) = *nb_p;
    if (curr_flag >= 0 && curr_flag < nbflags - 1)
        *nb_p += all_flags[j].func(valist, &f[i + 1]);
    if (curr_flag == nbflags - 1)
        curr_flag = NOT_A_FORMAT;
    return (curr_flag);
}

int my_printf(const char *f, ...)
{
    int nb_printed = 0;
    va_list valist;
    va_start(valist, f);
    for (int i = 0; f[i] != '\0'; i++) {
        int format = put_formats(f, i, valist, &nb_printed);
        if (format == NOT_A_FORMAT) {
            i--;
            nb_printed += my_putchar('%');
        }
        i += pass_multic_form(&f[i]);
        if (format != -1)
            i++;
        else
            nb_printed += my_putchar(f[i]);
    }
    va_end(valist);
    return (nb_printed - 1);
}
