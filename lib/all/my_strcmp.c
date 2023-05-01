/*
** EPITECH PROJECT, 2022
** my_strcmp.c
** File description:
** Return the int comp between 2 strings
*/

#include <stddef.h>

int my_strcmp(char const *s1, char const *s2)
{
    if (s1 == NULL || s2 == NULL)
        return (42);
    const unsigned char *p1 = (const unsigned char *)s1;
    const unsigned char *p2 = (const unsigned char *)s2;
    while (*p1) {
        unsigned char c1 = (unsigned char)*p1;
        unsigned char c2 = (unsigned char)*p2;
        if (!c2)
            return c1;
        if (c2 != c1)
            return c1 - c2;
        p1++;
        p2++;
    }
    return (*p1 - *p2);
}
