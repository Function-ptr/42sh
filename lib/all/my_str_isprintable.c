/*
** EPITECH PROJECT, 2022
** my_str_isprintable.c
** File description:
** Returns 1 if the str is printable else 0
*/

int my_str_isprintable(char *str)
{
    if (str == "")
        return (1);
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < 32)
            return (0);
    }
    return (1);
}
