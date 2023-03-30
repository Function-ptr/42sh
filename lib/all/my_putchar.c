/*
** EPITECH PROJECT, 2022
** my_putchar.c
** File description:
** my_putchar
*/

#include <unistd.h>
#include <stdarg.h>

int my_pc(va_list valist, char *ptr)
{
    int c = va_arg(valist, int);
    write(1, &c, 1);
    return (1);
}

int my_putchar(char c)
{
    write(1, &c, 1);
    return (1);
}

int my_put_percent(va_list valist, char *ptr)
{
    char p = '%';
    write(1, &p, 1);
    return (1);
}
