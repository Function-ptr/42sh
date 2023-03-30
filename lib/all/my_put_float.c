/*
** EPITECH PROJECT, 2022
** my_put_float.c
** File description:
** Print a float to the screen
*/

int my_put_nbr(int n);
void my_putchar(char c);

void my_put_float(float f, int dec)
{
    int tmp = (int)f;
    my_put_nbr(tmp);
    f -= tmp;
    my_putchar('.');
    for (int i = 0; i < dec; i++) {
        f *= 10;
        tmp = (int)f;
        my_put_nbr(tmp);
        f -= tmp;
    }
}
