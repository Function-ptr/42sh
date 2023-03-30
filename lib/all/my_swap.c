/*
** EPITECH PROJECT, 2022
** my_swap.c
** File description:
** Swap the content of 2 integers
*/

void my_swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
