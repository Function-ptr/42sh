/*
** EPITECH PROJECT, 2023
** smart_strtok.c
** File description:
** parse `string` into tokens
** delimiters are chars for which the function
** pointer `is_delimiter` returns true
*/

#include "parsing.h"

bool is_delimiter(const char *string, int i)
{
    char *delimiters = " \t\n";
    for (int j = 0; delimiters[j]; j++) {
        if (string[i] == delimiters[j] && !(i > 0 && string[i - 1] == '\\'))
            return true;
    }
    return false;
}

bool is_command_delimiter(const char *string, int i)
{
    char *delimiters = ";|";
    for (int j = 0; delimiters[j]; j++) {
        if (string[i] == delimiters[j] && !(i > 0 && string[i - 1] == '\\'))
            return true;
    }
    return false;
}

char *smart_strtok(char *string, bool (*is_delimiter)(const char *, int))
{
    if (!string)
        return NULL;
    int start = 0;
    while (is_delimiter(string, start))
        start += 1;
    for (int i = start; string[i]; i++) {
        if (is_delimiter(string, i)) {
            string[i] = '\0';
            return (string + start);
        }
    }
    return (string + start);
}
