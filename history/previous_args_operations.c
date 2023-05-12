/*
** EPITECH PROJECT, 2023
** previous_args_operations.c
** File description:
** Previous args operations (!)
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
#include "history.h"
#include "parsing.h"
#include "my.h"

long get_arg(char **input, int argslen)
{
    long arg;
    if ((*input)[2] != '*' && (*input)[2] != '$' && (*input)[2] != '^')
        arg = strtol(*input + 2, NULL, 10);
    else
        arg = (*input)[2] == '$' ? argslen - 1 :
            ((*input)[2] == '^' ? 1 : -1);
    return (arg);
}

void operate_on_single_arg(char **input, history_t *history)
{
    char *line = history_get_line_from_offset(history, 1);
    char **args = separate_args(line);
    int argslen = my_char_arraylen(args);
    long arg = get_arg(input, argslen);
    free(line);
    if (arg >= argslen) {
        fprintf(stderr, "Bad ! arg selector.\n");
        return;
    }
    free(*input);
    if (arg == -1)
        *input = word_array_to_command(args, NULL);
    else
        *input = strdup(args[arg]);
    *input = reallocarray(*input, strlen(*input) + 2, sizeof(char));
    strncpy(*input + strlen(*input), "\n\0", 2);
    printf("%s", *input);
    for (int i = 0; i < argslen; i++)
        free(args[i]);
    free(args);
}

void get_arg_range(char **input, int *limits, int argslen)
{
    char *sep = strchr(*input, '-'), *sepdup = sep;
    if (sep == NULL && (*input)[2] == '*') {
        if (argslen == 1) {
            limits[0] = -1;
            limits[1] = -1;
        } else {
            limits[0] = 1;
            limits[1] = argslen - 1;
        }
        return;
    } char *starsep = strchr(*input, '*');
    if (starsep != NULL) {
        limits[0] = (int)strtol(*input + 2, NULL, 10);
        limits[1] = argslen - 1;
        return;
    }
    limits[0] = *input + 2 != sep ? (int)strtol(*input + 2, &sepdup, 10) : 0;
    limits[1] = *(sep + 1) != '\n' ? (int)strtol(sep + 1, NULL, 10) :
        argslen - 2;
}

void process_new_input_range(char **input, const int limits[2], char **args,
    int argslen)
{
    free(*input);
    char *selargs[limits[1] - limits[0] + 2];
    memset(selargs, 0, sizeof(char*) * (limits[1] - limits[0] + 2));
    for (int i = limits[0], j = 0; i <= limits[1] && i < argslen; i++, j++)
        selargs[j] = args[i];
    *input = word_array_to_command(selargs, NULL);
    *input = reallocarray(*input, strlen(*input) + 2, sizeof(char));
    strncpy(*input + strlen(*input), "\n\0", 2);
    printf("%s", *input);
    for (int i = 0; i < argslen; i++) free(args[i]);
    free(args);
}

void operate_on_arg_range(char **input, history_t *history)
{
    char *line = history_get_line_from_offset(history, 1);
    char **args = separate_args(line);
    int argslen = my_char_arraylen(args);
    int limits[2] = {0, 0};
    get_arg_range(input, limits, argslen);
    if (limits[0] < 0 || limits[1] < 0) {
        if ((*input)[2] != '*')
            fprintf(stderr, "Bad ! arg selector.\n");
        for (int i = 0; i < argslen; i++) free(args[i]);
        free(args);
        free(line);
        return;
    }
    free(line);
    process_new_input_range(input, limits, args, argslen);
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
