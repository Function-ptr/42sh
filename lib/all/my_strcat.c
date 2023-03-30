/*
** EPITECH PROJECT, 2022
** my_strcat.c
** File description:
** Concatenates 2 strings
*/

char *my_strcat(char *dest, char const *str)
{
    int i;
    for (i = 0; dest[i] != '\0'; i++) {
    }
    for (int j = 0; str[j] != '\0'; j++) {
        dest[i] = str[j];
        i++;
    }
    return (dest);
}
