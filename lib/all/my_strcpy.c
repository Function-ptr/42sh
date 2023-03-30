/*
** EPITECH PROJECT, 2022
** my_strcpy.c
** File description:
** Copy a string to another
*/

char *my_strcpy(char *dest, char const *str)
{
    int i = 0;

    for (i; str[i] != '\0'; i++) {
        dest[i] = str[i];
    }
    dest[i] = '\0';
    return (dest);
}
