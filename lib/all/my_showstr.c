/*
** EPITECH PROJECT, 2022
** my_putstr.c
** File description:
** Print the string and unprintable chars in hex
*/

#include <unistd.h>
int my_putstr(char const *str);
int my_putnbr_base(int nbr, const char *str);
void my_putchar(char c);

int my_showstr(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        int printed = 0;
        if (str[i] < 16 ) {
            my_putstr("\\0");
            my_putnbr_base(str[i], "0123456789abcdef");
            printed = 1;
        }
        if (str[i] < 32 && printed == 0) {
            my_putchar('\\');
            my_putnbr_base(str[i], "0123456789abcdef");
            printed = 1;
        }
        if (printed == 0){
            my_putchar(str[i]);
        }
    }
    return (0);
}
