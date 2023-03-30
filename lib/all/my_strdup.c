/*
** EPITECH PROJECT, 2022
** my_strdup.c
** File description:
** Duplicates a string and returns a pointer
*/

#include <stdlib.h>
int my_strlen(char const *str);

char *my_strdup(char const *str)
{
    int len = my_strlen(str);
    char *result = malloc((len + 1) * sizeof(char));
    for (int i = 0; i < len; i++)
        result[i] = str[i];
    result[len] = 0;
    return (result);
}

char *my_strndup(char const *str, int len)
{
    char *result = malloc((len + 1) * sizeof(char));
    for (int i = 0; str[i] != 0 && i < len; i++)
        result[i] = str[i];
    result[len] = 0;
    return (result);
}
