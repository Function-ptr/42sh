/*
** EPITECH PROJECT, 2023
** inhibitors.c
** File description:
** escape characters that need to be escaped
*/

#include "minishell.h"

char *strdup_without_backslash(const char *src)
{
    char *res = calloc(strlen(src) + 1, 1);
    int len = strlen(src);
    int nb_escape = 0;
    for (int i = 0; i + nb_escape < len; i++) {
        if (src[i] == '\\') {
            nb_escape += 1;
            res[i] = src[i + nb_escape];
            continue;
        }
        res[i] = src[i + nb_escape];
    }
    return res;
}

char get_escape_char(char c)
{
    escape_char_t escape_chars[11] = {
        {'a', '\a'},
        {'b', '\b'},
        {'c', '\0'},
        {'e', '\e'},
        {'f', '\f'},
        {'n', '\n'},
        {'r', '\r'},
        {'t', '\t'},
        {'v', '\v'},
        {'\\', '\\'},
        {'0', -1}
    };
    for (int i = 0; i < 11; i++) {
        if (escape_chars[i].original == c)
            return (escape_chars[i].escaped);
    }
    return (c);
}
