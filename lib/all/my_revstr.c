/*
** EPITECH PROJECT, 2022
** my_revstr.c
** File description:
** Returns a reversed str
*/

int my_strlen(char const *str);

char *my_revstr(char *str)
{
    int len = my_strlen(str) - 1;
    int limit = len / 2;

    for (int i = 0; i <= limit; i++) {
        int tmp = str[i];
        str[i] = str[len - i];
        str[len - i] = tmp;
    }
    return (str);
}
