/*
** EPITECH PROJECT, 2023
** inhibitors.c
** File description:
** escape characters that need to be escaped
*/

#include "minishell.h"

char *strdup_without_backslash(const char *src)
{
    int len = strlen(src);
    char *res = calloc(len + 1, 1);
    bool backslash = false;
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (src[i] == '\\' && !backslash) {
            backslash = true;
            continue;
        }
        res[j++] = src[i];
        backslash = false;
    }
    return res;
}
