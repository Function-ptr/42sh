/*
** EPITECH PROJECT, 2022
** my_strncpy.c
** File description:
** Copies n bytes from a string to another
*/

char *my_strncpy(char *dest, char const *str, int n)
{
    int i;
    for (i = 0; i < n && str[i] != '\0'; i++)
        dest[i] = str[i];
    for (; i < n; i++)
        dest[i] = '\0';
    return (dest);
}
