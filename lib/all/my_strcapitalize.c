/*
** EPITECH PROJECT, 2022
** my_strcapitalize.c
** File description:
** Capitalize the first letter of each word
*/

char *my_strcapitalize(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if ((i == 0 || str[i - 1] < 48) && (str[i] > 96 && str[i] < 123)) {
            str[i] -= 32;
        }
        if ((str[i] >= 65 && str[i] <= 90) && str[i - 1] > 47) {
            str[i] += 32;
        }
    }
    return (str);
}
