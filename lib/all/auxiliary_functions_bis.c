/*
** EPITECH PROJECT, 2022
** auxiliary_functions_bis.c
** File description:
** auxiliary functions for my_printf (4 / 5)
*/

int my_getnbr_len(int nbr)
{
    int i;
    for (i = 0; nbr > 0; i++) {
        nbr /= 10;
    }
    return (i);
}

int my_ustrlen(unsigned char const *str)
{
    int len = 0;
    for (; str[len] != '\0'; len++) {
    }
    return (len);
}

unsigned char *my_revstr(unsigned char *str)
{
    int len = my_ustrlen(str) - 1;
    int limit = len / 2;

    for (int i = 0; i <= limit; i++) {
        int tmp = str[i];
        str[i] = str[len - i];
        str[len - i] = tmp;
    }
    return (str);
}

char *set_str(char *base, char *news)
{
    for (int i = 0; base[i] != '\0' && news[i] != '\0'; i++) {
        base[i] = news[i];
    }
    return (base);
}
