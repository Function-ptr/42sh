/*
** EPITECH PROJECT, 2022
** my_is_prime.c
** File description:
** Return if the number given as a parameter is prime
*/

int my_is_prime(int n)
{
    if (n < 2)
        return (0);
    for (int i = 2; i < n; i++) {
        if ((n % i) == 0)
            return (0);
    }
    return (1);
}
