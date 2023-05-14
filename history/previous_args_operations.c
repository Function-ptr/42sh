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
#include "execute.h"
#include "parsing.h"
#include "my.h"

long get_arg(char *input, int32_t argslen)
{
    int32_t arg;
    if (input[2] != '*' && input[2] != '$' && input[2] != '^')
        arg = (int32_t)strtol(input + 2, NULL, 10);
    else
        arg = input[2] == '$' ? argslen - 1 :
            (input[2] == '^' ? 1 : -1);
    return (arg);
}

void operate_on_single_arg(char *input, history_t *history)
{
    if (input == NULL) return;
    char *line = history_get_line_from_offset(history, 1), *r;
    char **args = separate_args(line);
    int32_t argslen = my_char_arraylen(args);
    long arg = get_arg(input, argslen); free(line);
    if (arg >= argslen) {
        fprintf(stderr, "Bad ! arg selector.\n");
        return;
    }
    if (arg == -1) r = word_array_to_command(args, NULL);
    else
        r = strdup(args[arg]);
    if (r == NULL) return;
    int len = (int)strlen(r);
    memset(input, 0, strlen(input));
    strcpy(input, r); strcpy(input + len, "\n\0");
    free(r);
    printf("%s", input);
    for (int i = 0; i < argslen; i++) free(args[i]);
    free(args);
}

void get_arg_range(char *input, int *limits, int32_t argslen)
{
    if (input == NULL) return;
    char *sep = strchr(input, '-'), *sepdup = sep;
    if (sep == NULL && (input)[2] == '*') {
        if (argslen == 1) {
            limits[0] = -1;
            limits[1] = -1;
        } else {
            limits[0] = 1;
            limits[1] = argslen - 1;
        } return;
    }
    char *starsep = strchr(input, '*');
    if (starsep != NULL) {
        limits[0] = strtol(input + 2, NULL, 10);
        limits[1] = argslen - 1; return;
    } limits[0] = input + 2 != sep ? (int)strtol(input + 2, &sepdup, 10) : 0;
    limits[1] = *(sep + 1) != '\n' ? (int)strtol(sep + 1, NULL, 10)
            : argslen - 2;
}

void process_new_input_range(char *input, int limits[2], char **args,
    int32_t argslen)
{
    char *selargs[limits[1] - limits[0] + 2];
    memset(selargs, 0, sizeof(char*) * (limits[1] - limits[0] + 2));
    for (int i = limits[0], j = 0; i <= limits[1] && i < argslen; i++, j++)
        selargs[j] = args[i];
    char *r = word_array_to_command(selargs, NULL);
    int len = (int)strlen(r);
    memset(input, 0, strlen(input));
    strcpy(input, r);
    strcpy(input + len, "\n\0");
    printf("%s", input);
    free(r);
    for (int i = 0; i < argslen; i++) free(args[i]);
    free(args);
}

void operate_on_arg_range(char *input, history_t *history)
{
    char *line = history_get_line_from_offset(history, 1);
    char **args = separate_args(line);
    int32_t argslen = my_char_arraylen(args);
    int limits[2] = {0, 0};
    get_arg_range(input, limits, argslen);
    if (limits[0] < 0 || limits[1] < 0) {
        if (input[2] != '*')
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
