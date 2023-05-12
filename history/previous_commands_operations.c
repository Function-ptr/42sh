/*
** EPITECH PROJECT, 2023
** previous_commands_operations.c
** File description:
** Previous commands implementation (!)
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

size_t get_offset_strstr(char *input, history_t *history, size_t lenh)
{
    for (size_t i = 1; i < lenh; i++) {
        char *s = history_get_line_from_offset(history, i);
        if (s == NULL)
            return -1;
        char *r = strstr(s, input);
        free(s);
        if (r)
            return i;
    }
    return -1;
}

size_t get_offset_from_str(char *input, history_t *history)
{
    size_t lenh = history->len_session_history + history->len_file;
    if (input[1] == '?') {
        char *str;
        if (strchr(input, '?') != strrchr(input, '?'))
            str = strndup(input + 2, strrchr(input, '?') - strchr(input, '?'));
        else
            str = strdup(input + 2);
        size_t o = get_offset_strstr(str, history, lenh);
        free(str);
        return o;
    }
    size_t len = strlen(input + 1);
    for (size_t i = 1; i < lenh; i++) {
        char *s = history_get_line_from_offset(history, i);
        if (s == NULL) return -1;
        int r = strncmp(s, input + 1, len - 1);
        free(s);
        if (!r) return i;
    }
    return -1;
}

void operate_on_line_offset(char **input, history_t *history)
{
    size_t offset = -1, s = history->len_session_history + history->len_file;
    if (isnum((*input)[1])) {
        size_t val = strtol(*input + 1, NULL, 10);
        if (val > history->len_session_history + history->len_file) {
            fprintf(stderr, "%li: Event not found\n", val);
            return;
        }
        offset = s - val;
    } if ((*input)[1] == '-' && isnum((*input)[2])) {
        offset = strtol(*input + 2, NULL, 10);
        if (offset > history->len_session_history + history->len_file) {
            fprintf(stderr, "%li: Event not found\n", offset);
            return;
        }
    }
    if (offset == -1) offset = get_offset_from_str(*input, history);
    if (offset == -1) return;
    free(*input);
    *input = history_get_line_from_offset(history, offset);
}

void operate_on_previous_command(char *input, history_t *history)
{
    if (input[0] != '!') return;
    if (history == NULL) {
        fprintf(stderr, "history: Unable to load previous history\n");
        return;
    }
    if ((input)[1] != ':') {
        if ((input)[1] != '!') operate_on_line_offset(&input, history);
        else {
            free(input);
            input = history_get_line_from_offset(history, 1);
        } if ((input)[0] != '!') printf("%s", input);
        else
            fprintf(stderr, "%s: Event not found.\n", input);
        return;
    }
    if ((strchr(input, '*') || strchr(input, '-')) &&
        (input)[2] != '^' && (input)[2] != '$')
        operate_on_arg_range(&input, history);
    else
        operate_on_single_arg(&input, history);
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
