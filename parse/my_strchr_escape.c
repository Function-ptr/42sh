/*
** EPITECH PROJECT, 2023
** my_strchr_escape.c
** File description:
** search for a char in a string, but ignore escaped chars
*/

#include "minishell.h"
char *my_strchr_escape(char *str, char c)
{
    for (int i = 0; str[i] != 0; i++) {
        if (str[i] == c && !(i > 0 && str[i-1] == '\\'))
            return (str + i);
    }
    return (NULL);
}

char *my_strrchr_escape(char *str, char c)
{
    for (int i = my_strlen(str) - 1; i >= 0; i--) {
        if (str[i] == c && !(i > 0 && str[i-1] == '\\'))
            return (str + i);
    }
    return (NULL);
}
