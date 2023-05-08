/*
** EPITECH PROJECT, 2023
** cut_input_to_commands.c
** File description:
** cut command line input to individual commands (ls | grep .c => ls and grep)
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
#include "parsing.h"

int separate_commands(int nb_cmds, char *input, command_t **commands)
{
    char *tmp = strdup(input);
    int status = 1;
    command_t *previous = NULL;
    for (int i = 0, pos = 0, tp = 0; tp < nb_cmds; i++, tp++) {
        input = smart_strtok(input, is_command_delimiter);
        if (!input) break;
        pos += strlen(input);
        int *statuses[2] = {&i, &status};
        char sep[2] = {tmp[pos], tmp[pos] && strchr("&|", tmp[pos + 1])
            ? tmp[pos + 1] : 0};
        commands[i] = parse_single_command(input, previous, sep, statuses);
        status *= commands[i] ? 1 : 0;
        pos += 1;
        previous = commands[i];
        for (int j = i + 1; j <= nb_cmds; j++)
            commands[j] = NULL;
        input += strlen(input) + 1;
    }
    free(tmp);
    return status;
}

int get_nb_commands(char *input, int *has_parentheses)
{
    int nb_commands = 1, curr_parentheses = 0;
    bool inquote = false;
    for (int i = 0; input[i] != 0; i++) {
        if ((((i > 0 && input[i] == '|' && input[i - 1] != '|' &&
            input[i + 1] != '|') && !(i > 0 && input[i - 1] == '\\')) ||
            (input[i] == ';' && !(i > 0 && input[i - 1] == '\\')) ||
            (i > 0 && input[i] == '|' && input[i - 1] == '|') ||
            (i > 0 && input[i] == '&' && input[i - 1] == '&')) &&
            !curr_parentheses) nb_commands += 1;
        if (input[i] == '"') inquote = !inquote;
        if (input[i] == '(' && !inquote) {
            *has_parentheses = true;
            curr_parentheses += 1;
        } if (input[i] == ')' && !inquote) curr_parentheses -= 1;
    }
    if (curr_parentheses != 0) {
        fprintf(stderr, "Too many %c's\n", curr_parentheses > 0 ? '(' : ')');
        return -1;
    }
    return nb_commands;
}

command_t **cut_input_to_commands(char *input)
{
    int len = (int)strlen(input), has_parentheses = false, status = 1;
    input[len - 1] = 0;
    int nb_cmds = get_nb_commands(input, &has_parentheses);
    if (nb_cmds == -1) return NULL;
    command_t **cmds = calloc(nb_cmds + 1, sizeof(command_t*));
    if (!has_parentheses)
        status = separate_commands(nb_cmds, input, cmds);
    else
        status = separate_command_with_parentheses(nb_cmds, input, cmds);
    if (!status) {
        free_commands(cmds);
        return NULL;
    }
    return cmds;
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
