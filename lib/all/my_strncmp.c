/*
** EPITECH PROJECT, 2022
** my_strncmp.c
** File description:
** Compare the n bytes of 2 strings
*/
#include <stddef.h>
int my_strncmp(char const *s1, char const *s2, int n)
{
    if (s1 == NULL || s2 == NULL)
        return (42);
    const unsigned char *p1 = (const unsigned char *)s1;
    const unsigned char *p2 = (const unsigned char *)s2;
    unsigned char c1, c2;
    int i = 0;
    while (*p1 && i < n) {
        c1 = (unsigned char)*p1; c2 = (unsigned char)*p2;
        if (!c2)
            return c1;
        if (c2 != c1)
            return c1 - c2;
        p1++;
        p2++;
        i++;
    }
    if (!*p1)
        return -(*p2);
    return (0);
}
