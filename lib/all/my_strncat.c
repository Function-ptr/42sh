/*
** EPITECH PROJECT, 2022
** my_strcat.c
** File description:
** Concatenates 2 strings
*/

char *my_strncat(char *dest, char const *str, int n)
{
    int i;
    int j;

    for (i = 0; dest[i] != '\0'; i++) {
    }
    for (j = 0; str[j] != '\0' && j < n; j++) {
        dest[i] = str[j];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}
