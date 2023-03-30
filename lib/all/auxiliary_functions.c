/*
** EPITECH PROJECT, 2022
** auxiliary_functions.c
** File description:
** auxiliary functions (FULL)
*/

#include "include/printf.h"

int my_strlen(char *str)
{
    int len = 0;
    for (; str[len] != '\0'; len++);
    return (len);
}

int my_isnumeric(char c)
{
    if (c > 47 && c < 58)
        return (1);
    return (0);
}

double my_power_it(double n, int p)
{
    double result = 1;
    if (p < 0) {
        return (0);
    } else if (p == 0) {
        return (1);
    }
    for (int i = 0; i < p; i++) {
        result *= n;
    }
    return (result);
}

double power_neg(double n, int p)
{
    double result = 1;
    if (p == 0) {
        return (1);
    }
    for (int i = 0; i < p; i++) {
        result /= n;
    }
    return (result);
}

int my_getnbr_len_fs(const char *str)
{
    int nbr = my_getnbr(str);
    int i;
    for (i = 0; nbr > 0; i++) {
        nbr /= 10;
    }
    return (i);
}
