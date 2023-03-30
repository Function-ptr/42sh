/*
** EPITECH PROJECT, 2023
** my_calloc.c
** File description:
** my calloc
*/

#include <stdlib.h>

void *my_memset(void *p, size_t n, char byte)
{
    char *data = (char*)p;
    for (int i = 0; i < n; i++)
        data[i] = byte;
    return (p);
}

void *my_calloc(size_t len, size_t datasize, char byte)
{
    void *res = malloc(datasize * len + 1);
    res = my_memset(res, len, byte);
    return (res);
}
