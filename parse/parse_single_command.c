/*
** EPITECH PROJECT, 2023
** parse_single_command.c
** File description:
** parse a single command and get all of it's redirections / pipes
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

bool command_has_parentheses(char *input)
{
    int inquote = false, parlayer = 0, haspar = false;
    for (int i = 0; input[i]; i++) {
        if (input[i] == '"') inquote = !inquote;
        if (!inquote && input[i] == '(') {
            haspar = true;
            parlayer += 1;
        } if (!inquote && input[i] == ')')
            parlayer -= 1;
    }
    return haspar;
}

void init_command(command_t *command, command_t *prev, char next_sep[2])
{
    command->in_fd = STDIN_FILENO;
    command->out_fd = STDOUT_FILENO;
    command->pipe_in_fd = -1;
    command->pipe_out = false;
    command->pipe_in = false;
    command->condition = None;
    command->depth = Curr_shell;
    strncpy(command->next_separator, next_sep, 2);
    if (prev != NULL && prev->pipe_out) command->pipe_in = true;
    if (next_sep[0] == '|' && !next_sep[1]) command->pipe_out = true;
    if (next_sep[0] == '&' && next_sep[1] == '&') command->condition = AND;
    if (next_sep[0] == '|' && next_sep[1] == '|') command->condition = OR;
    if (command_has_parentheses(command->command)) command->depth = Parentheses;
    if (strchr(command->command, '`')) command->depth = Backticks;
}

bool has_ambiguous_redirection_in(command_t *command, char *comm)
{
    char *redirection_in = my_strchr_escape(comm, '<');
    char *redirection_in_word = my_strrchr_escape(comm, '<');
    if (command->pipe_in && redirection_in != NULL) {
        ambigous_redirection(true);
        return true;
    }

    if (redirection_in_word != NULL &&
        redirection_in_word != redirection_in + 1 &&
        redirection_in_word != redirection_in) {
        ambigous_redirection(true);
        return true;
    }

    return false;
}

bool has_ambiguous_redirection_out(command_t *command, char *comm)
{
    char *redirection_out = my_strchr_escape(comm, '>');
    char *redirection_out_append = my_strrchr_escape(comm, '>');
    if (command->pipe_out && redirection_out != NULL) {
        ambigous_redirection(false);
        return true;
    }

    if (redirection_out_append != NULL &&
        redirection_out_append != redirection_out + 1 &&
        redirection_out_append != redirection_out) {
        ambigous_redirection(false);
        return true;
    }

    return false;
}

command_t *parse_single_command(char *comm, command_t *prev, char next_sep[2],
    int **statuses)
{
    command_t *command = malloc(sizeof(command_t));
    int *i = statuses[0], *status = statuses[1];
    command->command = comm;
    init_command(command, prev, next_sep);
    if (has_ambiguous_redirection_in(command, comm) ||
        has_ambiguous_redirection_out(command, comm)) {
        free(command);
        return NULL;
    }
    detect_redirections(command, comm, next_sep, status);
    if (command->command == NULL) {
        *i = (*i > 0) ? (*i - 1) : 0;
        free_command(command);
        return prev;
    }
    return command;
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
