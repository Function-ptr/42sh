/*
** EPITECH PROJECT, 2022
** my_isneg.c
** File description:
** Prints the sign of the integer
*/

void my_putchar(char c);

int my_isneg(int n)
{
    if (n < 0) {
        my_putchar(78);
    } else {
        my_putchar(80);
    }
    return (0);
}
