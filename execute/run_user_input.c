/*
** EPITECH PROJECT, 2023
** run_user_input.c
** File description:
** parse and execute the user input
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
#include "parsing.h"

int run_command(command_t *command, int *exiting, envdata_t *env)
{
    int status = 0;
    if (!command->command || command->command[0] == 0) {
        free_command(command);
        return (status);
    }
    if (load_redirections_for_command(command) == -1)
        return (-1);
    status = detect_command_type_and_run(command, exiting, env);
    free_command(command);
    return (status);
}

void process_quote(char **str, char *quote_start, char *quote_end)
{
    char *inside_quote_processed = malloc((quote_end - quote_start - 1) * 2);

    for (int i = 0; quote_start + i < quote_end - 1; i++) {
        inside_quote_processed[i * 2] = '\\';
        inside_quote_processed[i * 2 + 1] = quote_start[i + 1];
    }

    int str_len = strlen(*str);
    char *new_str = calloc(str_len + quote_end - quote_start - 2, 1);

    int i = 0;
    for (; *str + i < quote_start; i++)
        new_str[i] = (*str)[i];
    for (int j = 0; j < (quote_end - quote_start - 1) * 2; j++, i++)
        new_str[i] = inside_quote_processed[j];
    for (char *c = quote_end + 1; c < *str + str_len; c++, i++)
        new_str[i] = *c;

    free(inside_quote_processed);
    *str = new_str;
}

int find_quote(char **str)
{
    char * simple_quote_start = my_strchr_escape(*str, '\'');
    char * double_quote_start = my_strchr_escape(*str, '"');

    char * quote_start =
        double_quote_start == NULL ? simple_quote_start :
        simple_quote_start == NULL ? double_quote_start :
        MIN(double_quote_start, simple_quote_start);

    if (quote_start == NULL)
        return -1;

    char *quote_end = strchr(quote_start + 1, *quote_start);

    if (quote_end == NULL)
        return *quote_start;

    process_quote(str, quote_start, quote_end);

    return 0;
}

bool process_quotes(char **str)
{
    int status = 0;
    while (true) {
        status = find_quote(str);
        if (status == -1) {
            return false;
        }
        if (status == '\'') {
            printf("Unmatched '''.\n");
            return true;
        }
        if (status == '"') {
            printf("Unmatched '\"'.\n");
            return true;
        }
    }
}

int run_user_input(char *input, envdata_t *env, int *exiting)
{
    if (process_quotes(&input))
        return -1;
    command_t **commands = cut_input_to_commands(input);
    int status = 0, nb_commands = 0, i = 0;
    if (commands == NULL)
        return status;
    for (; commands[nb_commands] != NULL; nb_commands++);
    int *data[3] = {&i, &nb_commands, exiting};
    for (; i < nb_commands; i++) {
        status = 0;
        if (!commands[i]->pipe_out)
            status = run_command(commands[i], exiting, env);
        else
            status = loop_over_pipes(commands, env, data);
        if (status == -1)
            return (-1);
    }
    free(commands);
    return (status);
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
