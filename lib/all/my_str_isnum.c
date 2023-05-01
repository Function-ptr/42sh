/*
** EPITECH PROJECT, 2022
** my_str_isnum.c
** File description:
** Returns 1 if the string is only made of digits else 0
*/

int my_str_isnum(char *str)
{
    if (!*str)
        return (1);
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < 48 || str[i] > 57)
            return (0);
    }
    return (1);
}
