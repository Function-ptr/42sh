/*
** EPITECH PROJECT, 2022
** my_compute_square_root.c
** File description:
** Returns the square root if it is an integer else 0
*/

int my_compute_square_root(int n)
{
    for (int i = 0; i <= 46340; i++) {
        if (i * i == n) {
            return (i);
        }
        if (i * i > n) {
            return (0);
        }
    }
    return (0);
}
