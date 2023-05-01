/*
** EPITECH PROJECT, 2022
** my_str_to_word_array.c
** File description:
** Convert a string to an array of words
*/

#include <stdlib.h>
#include <string.h>

int is_sep(char c, char *sep)
{
    for (int i = 0; sep[i] != '\0'; i++)
        if (c == sep[i]) return (1);
    return (0);
}

int nb_words(char const *str, int len, char *sep)
{
    int nb = 0;
    int word_found = 0;
    for (int i = 0; i < len; i++) {
        if (!is_sep(str[i], sep) && word_found) {
            continue;
        }
        if (!is_sep(str[i], sep) && word_found == 0) {
            nb = nb + 1;
            word_found = 1;
        } else {
            word_found = 0;
        }
    }
    return (nb);
}

int *get_word_indexes(char const *str, int len, int nbword, char *sep)
{
    int *warr = malloc(sizeof(int) * nbword);
    int nb = 0;
    int word_found = 0;
    for (int i = 0; i < len; i++) {
        if (!is_sep(str[i], sep) && word_found) {
            continue;
        }
        if (!is_sep(str[i], sep) && word_found == 0) {
            warr[nb] = i;
            nb++;
            word_found = 1;
        } else {
            word_found = 0;
        }
    }
    return (warr);
}

int get_word_len(char const *str, int index, char *sep)
{
    int i = index;
    for (; str[i] != 0 && !is_sep(str[i], sep); i++);
    return (i - index);
}

char **my_str_to_word_array(char const *str, char *sep)
{
    int len = strlen(str);
    int nbword = nb_words(str, len, sep);
    int *windexes = get_word_indexes(str, len, nbword, sep);
    char **arr = malloc((nbword + 1) * sizeof(char *));
    int i = 0;
    for (; i < nbword; i++) {
        int wlen = get_word_len(str, windexes[i], sep);
        char *word = malloc(sizeof(char) * (wlen + 1));
        int j = 0;
        for (; j < wlen; j++) {
            word[j] = str[windexes[i] + j];
        }
        word[j] = '\0';
        arr[i] = strdup(word);
        free(word);
    }
    arr[nbword] = NULL;
    free(windexes);
    return (arr);
}
