/*
** EPITECH PROJECT, 2022
** random.c
** File description:
** random generator
*/

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


long int random_wl(int bytes)
{
    if (bytes < 1 || bytes > 8)
        return (0);
    char data[bytes];
    long int res = 0;
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd == -1)
        return (0);
    read(fd, data, bytes);
    for (int i = 0; i < bytes - 1; i++) {
        res += data[i];
        res = res << 8;
    }
    res += data[bytes - 1];
    return (res);
}
