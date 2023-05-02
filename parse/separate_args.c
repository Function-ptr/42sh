/*
** EPITECH PROJECT, 2023
** separate_args.c
** File description:
** separate arguments
*/

#include "parsing.h"

int nb_args(char const *str, int len)
{
    int nb = 0;
    int word_found = 0;
    for (int i = 0; i < len; i++) {
        if (!is_delimiter(str, i) && word_found) {
            continue;
        }
        if (!is_delimiter(str, i) && word_found == 0) {
            nb = nb + 1;
            word_found = 1;
        } else {
            word_found = 0;
        }
    }
    return (nb);
}

int *get_arg_indexes(char const *str, int len, int nbword)
{
    int *warr = malloc(sizeof(int) * nbword);
    int nb = 0;
    int word_found = 0;
    for (int i = 0; i < len; i++) {
        if (!is_delimiter(str, i) && word_found) {
            continue;
        }
        if (!is_delimiter(str, i) && word_found == 0) {
            warr[nb] = i;
            nb++;
            word_found = 1;
        } else {
            word_found = 0;
        }
    }
    return (warr);
}

int get_arg_len(char const *str, int index)
{
    int i = index;
    for (; str[i] != 0 && !is_delimiter(str, i); i++);
    return (i - index);
}

char **separate_args(char const *str)
{
    int len = strlen(str);
    int nbword = nb_args(str, len);
    int *windexes = get_arg_indexes(str, len, nbword);
    char **arr = malloc((nbword + 1) * sizeof(char *));
    int i = 0;
    for (; i < nbword; i++) {
        int wlen = get_arg_len(str, windexes[i]);
        char *word = malloc(sizeof(char) * (wlen + 1));
        int j = 0;
        for (; j < wlen; j++) {
            word[j] = str[windexes[i] + j];
        }
        word[j] = '\0';
        arr[i] = strdup_without_backslash(word);
        free(word);
    }
    arr[nbword] = NULL;
    free(windexes);
    return (arr);
}
