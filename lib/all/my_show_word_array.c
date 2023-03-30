/*
** EPITECH PROJECT, 2022
** my_show_word_array.c
** File description:
** Print an array of words
*/

#include <stddef.h>
int my_putstr(char const *str);
void my_putchar(char c);

int my_show_word_array(char const **arr)
{
    for (int i = 0; arr[i] != NULL; i++) {
        my_putstr(arr[i]);
        my_putchar('\n');
    }
    return (0);
}
