/*
** EPITECH PROJECT, 2023
** quotes.c
** File description:
** quotes
*/

#include "parsing.h"

void process_quote(char **str, char *quote_start, char *quote_end)
{
    char *inside_quote_processed = malloc((quote_end - quote_start - 1) * 2);

    for (int i = 0; quote_start + i < quote_end - 1; i++) {
        inside_quote_processed[i * 2] = '\\';
        inside_quote_processed[i * 2 + 1] = quote_start[i + 1];
    }

    int str_len = strlen(*str);
    char *new_str = calloc(str_len + quote_end - quote_start - 2, 1);

    int i = 0;
    for (; *str + i < quote_start; i++)
        new_str[i] = (*str)[i];
    for (int j = 0; j < (quote_end - quote_start - 1) * 2; j++, i++)
        new_str[i] = inside_quote_processed[j];
    for (char *c = quote_end + 1; c < *str + str_len; c++, i++)
        new_str[i] = *c;
    free(*str);
    free(inside_quote_processed);
    *str = new_str;
}

int find_quote(char **str)
{
    char * simple_quote_start = my_strchr_escape(*str, '\'');
    char * double_quote_start = my_strchr_escape(*str, '"');

    char * quote_start =
        double_quote_start == NULL ? simple_quote_start :
        simple_quote_start == NULL ? double_quote_start :
        MIN(double_quote_start, simple_quote_start);

    if (quote_start == NULL)
        return -1;

    char *quote_end = strchr(quote_start + 1, *quote_start);

    if (quote_end == NULL)
        return *quote_start;

    process_quote(str, quote_start, quote_end);

    return 0;
}

bool process_quotes(char **str)
{
    while (true) {
        int status = find_quote(str);
        if (status == -1) {
            return false;
        }
        if (status == '\'') {
            printf("Unmatched '''.\n");
            free(*str);
            return true;
        }
        if (status == '"') {
            printf("Unmatched '\"'.\n");
            free(*str);
            return true;
        }
    }
}
