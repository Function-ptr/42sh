/*
** EPITECH PROJECT, 2022
** my_str_isalpha.c
** File description:
** Returns 1 if the str contains only letters else 0
*/

int my_str_isalpha(char const *str)
{
    if (str == "")
        return (1);
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < 65 || (str[i] > 90 && str[i] < 97) || str[i] > 122)
            return (0);
    }
    return (1);
}

int my_str_isalphanum(char *str)
{
    if (str == "")
        return (1);
    for (int i = 0; str[i] != '\0'; i++) {
        if ((str[i] >= 48 && str[i] <= 57) || (str[i] >= 65 && str[i] <= 90) ||
            (str[i] >= 97 && str[i] <= 122) || str[i] == '.' || str[i] == '_')
            continue;
        else
            return (0);
    }
    return (1);
}
