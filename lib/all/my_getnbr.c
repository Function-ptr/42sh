/*
** EPITECH PROJECT, 2022
** my_getnbr.c
** File description:
** my_getnbr
*/

int my_get_only_nbr(char const *str)
{
    int i = 0;
    int nb = 0;
    int neg = 1;

    while (str[i] == '-' || str[i] == '+') {
        if (str[i] == '-')
            neg = neg * -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9') {
        nb = nb * 10;
        nb = nb + str[i] - 48;
        i++;
    }
    return (nb * neg);
}

int get_sign(int i, int sign)
{
    if (i == 45) {
        return (-1);
    }
    if (i == 43) {
        if (sign == -1)
            return (-1);
        return (1);
    } else if (i >= 48 && i <= 57) {
        return (1);
    }
    if (sign == -1) {
        return (-1);
    } else {
        return (1);
    }
}

int process_int(int val, int i)
{
    i = i - 48;
    if ((val + i) * 10 < 0) {
        return (0);
    }
    return (val + i);
}

int my_getnbr(char const *str)
{
    int sign = 1;
    int num_found = 0;
    int val = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (num_found == 1 && (str[i] < 48 || str[i] > 71)) {
            break;
        }
        sign *= get_sign(str[i], sign);
        if (str[i] >= 48 && str[i] <= 71) {
            val = process_int(val, str[i]);
            num_found = 1;
        }
        if (val == 0 && num_found == 1)
            return (0);
        val = val * 10;
    }
    return ((val / 10) * sign);
}
