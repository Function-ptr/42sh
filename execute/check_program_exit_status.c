/*
** EPITECH PROJECT, 2023
** check_program_exit_status.c
** File description:
** check the program exit status
*/
/*
 __  __        _                            ___            ___
|  \/  |      | |                          / _ \          / _ \.
| \  / | _ __ | |       ___   __ _   ___  | (_) |        | (_) |
| |\/| || '__|| |      / _ \ / _` | / _ \  > _ <          \__, |
| |  | || |   | |____ |  __/| (_| || (_) || (_) |           / /
|_|  |_||_|   |______| \___| \__, | \___/  \___/           /_/
                              __/ |               ______
                             |___/               |______|
*/
#include "execute.h"

void check_if_signaled(int status)
{
    if (WIFSIGNALED(status)) {
        if (WTERMSIG(status) == SIGFPE)
            fprintf(stderr, "Floating exception");
        else
            fprintf(stderr, "%s", strsignal(WTERMSIG(status)));
        if (WCOREDUMP(status))
            fprintf(stderr, " (core dumped)");
        fprintf(stderr, "\n");
    }
}

void check_if_stopped(int status)
{
    if (WIFSTOPPED(status)) {
        fprintf(stderr, "%s", strsignal(WSTOPSIG(status)));
        if (WCOREDUMP(status))
            fprintf(stderr, " (core dumped)");
        fprintf(stderr, "\n");
    }
}

int check_exit_status(int status)
{
    check_if_signaled(status);
    check_if_stopped(status);
    return (WIFEXITED(status));
}
/*
⠀⠀⠀⠀⠀⠀⠀⠀⢀⡴⠊⠉⠉⢉⠏⠻⣍⠑⢲⠢⠤⣄⣀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⣻⣿⢟⣽⠿⠯⠛⡸⢹⠀⢹⠒⣊⡡⠜⠓⠢⣄⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⢀⡜⣿⣷⣽⠓⠀⢠⢂⣣⠋⠂⣾⠼⢌⠳⢄⢀⡠⠜⣣⡀⠀⠀
⠀⠀⠀⠀⠀⢠⢻⢱⣭⠷⠤⢅⠴⣡⡻⠃⠀⢠⠁⠀⢀⡱⠜⠍⢔⠊⠀⠹⡄⠀
⠀⠀⠀⠀⢀⣷⠌⠚⠷⠆⠠⠶⠭⢒⣁⠀⣤⠃⣀⢔⢋⡤⠊⠑⣄⠳⣄⠀⣧⠀
⠀⠀⠀⠀⠀⠑⠦⣀⡤⣄⠄⢄⣀⣠⣒⢦⡄⠩⠷⠦⠊⠀⠀⠀⠈⠣⡏⠢⣿⠀
⠀⠀⠀⠀⠀⠀⣸⢫⠟⣝⠞⣼⢲⡞⣞⠋⠋⠉⠋⠓⡄⠀⠀⠀⠀⠀⣨⠂⢸⡅
⠀⠀⠀⠀⠀⣰⠃⡨⠊⢀⡠⡌⢘⢇⠞⠀⠀⠀⠀⠂⠡⡄⠀⠀⢀⠞⢁⠔⢹⡇
⠀⠀⠀⠀⣰⣣⠞⢀⠔⢡⢢⠇⡘⠌⠀⠀⠀⠀⠀⠀⠠⡌⠢⡔⢁⡴⠁⠀⢸⠃
⠀⠀⠀⢠⠟⠁⠠⢊⠔⣡⢸⠀⠃⠁⠀⠀⠀⠀⠀⠀⠀⣯⠂⡀⢪⡀⠀⠀⢸⠀
⠀⢀⠔⣁⠐⠨⠀⠀⠈⠀⢄⠘⡀⠀⠈⢆⠀⠀⠀⠀⡠⢁⠜⠙⢦⠙⣦⠀⢸⠀
⡴⠁⠘⡁⣀⡡⠀⠀⠴⠒⠗⠋⠉⠉⡆⠀⠆⠄⠄⠘⠀⡎⠀⠀⠀⠑⢅⠑⢼⡀
⢯⣉⣓⠒⠒⠤⠤⣄⣀⣀⣀⣀⡀⠐⠁⠀⠀⠀⠒⠀⢀⡀⠀⠀⠀⠀⠀⠑⣌⣇
⠀⠈⢳⠄⠈⠀⠤⢄⣀⠀⢈⣉⡹⠯⡟⠁⠀⠀⠀⠀⢸⠀⠀⠂⠀⠀⡠⠚⣡⡿
⠀⢠⣋⣀⣀⣀⣀⠤⠭⢛⡩⠄⠒⠩⠂⢀⠄⠀⠀⠀⠈⢢⡀⠀⡠⠋⡩⠋⠀⢳
⠀⢹⠤⠬⠤⠬⠭⣉⣉⢃⠀⠀⣀⣀⠀⠁⠀⠀⠀⠀⡞⢺⡈⠋⡢⠊⠀⠀⠀⢸
⠀⠈⡆⠁⢀⠀⠀⠀⠉⠋⠉⠓⠂⠤⣀⡀⠀⠀⠀⠀⡧⠊⡠⠦⡈⠳⢄⠀⠀⠈
⠀⠀⢹⡜⠀⠁⠀⠀⠒⢤⡄⠤⠔⠶⠒⠛⠧⠀⠀⡼⡠⠊⠀⠀⠙⢦⡈⠳⡄⠀
⠀⠀⢸⠆⠀⠈⠀⠠⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⡜⢸⠀⠀⠀⠀⠀⠀⠑⢄⠈⢲
⠀⠀⢸⢀⠇⠀⠀⠀⠀⢀⠀⠀⠀⠀⠀⠀⡄⠊⢠⠃⠀⠀⠀⠀⠀⠀⠀⠈⡢⣸
⠀⠀⠈⠳⣤⣄⡀⠀⠀⠀⠈⠉⠉⠁⠒⠁⠀⠠⣏⠀⠀⠀⠀⠀⠀⢀⣔⠾⡿⠃
⠀⠀⠀⠀⠉⠙⠛⠒⠤⠤⣤⣄⣀⣀⣀⣔⣢⣀⣉⣂⣀⣀⣠⠴⠿⠛⠋
*/
