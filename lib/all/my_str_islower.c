/*
** EPITECH PROJECT, 2022
** my_str_islower.c
** File description:
** Returns 1 if the str is lowercase else 0
*/

int my_str_islower(char *str)
{
    if (!*str)
        return (1);
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < 97 || str[i] > 122)
            return (0);
    }
    return (1);
}
