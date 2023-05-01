/*
** EPITECH PROJECT, 2022
** my_str_isupper.c
** File description:
** Returns 1 if the str is uppercase else 0
*/

int my_str_isupper(char *str)
{
    if (!*str)
        return (1);
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < 65 || str[i] > 90)
            return (0);
    }
    return (1);
}
