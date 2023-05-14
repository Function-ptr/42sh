/*
** EPITECH PROJECT, 2023
** handle_redirections.c
** File description:
** handle redirections (detect and process)
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

void detect_redirections(command_t *command, char *comm, char next_sep[2],
    int *status)
{
    if (!comm) return;
    char *redirection_out = my_strchr_escape(comm, '>');
    char *redirection_out_append = my_strrchr_escape(comm, '>');
    char *redirection_in = my_strchr_escape(comm, '<');
    char *redirection_in_word = my_strrchr_escape(comm, '<');
    command->redirect_in = (redirection_in != NULL);
    command->redirect_in_word_wait = (redirection_in &&
        redirection_in_word == redirection_in + 1);
    command->redirect_out = (redirection_out != NULL);
    command->redirect_out_append = (redirection_out &&
        redirection_out_append == redirection_out + 1);
    command->awaited_word = NULL;
    command->command = remove_spaces_in_command(command->command,
        next_sep, command->pipe_in, status);
}

char *get_redirection_filename(char *str, int *size)
{
    for (; (*str == ' ' || *str == '\t' || *str == '>' || *str == '<') &&
        *str != 0; str++, *size += 1);

    if (*str == 0 || *str == ';' || *str == '|') {
        missing_name_for_redirection();
        return NULL;
    }

    int len = 0;
    for (; str[len] != ' ' && str[len] != '\t' && str[len] != '\n' && str[len];
        len++, *size += 1);

    return strndup(str, len);
}

int open_output_file_descriptor(command_t *command, char *comm)
{
    if (!comm) return 1;
    char *redirection_out = strchr(comm, '>');
    if (!redirection_out) return 1;
    char *redirection_out_append = strrchr(comm, '>');
    int size = 0;
    char *file = get_redirection_filename(redirection_out_append + 1, &size);
    if (file == NULL)
        return 1;
    int open_flag = (command->redirect_out_append ? O_APPEND : O_TRUNC);
    command->out_fd = open(file, O_WRONLY | O_CREAT | open_flag,
        S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    free(file);
    memset(redirection_out, ' ', size + (command->redirect_out_append ? 2 : 1));
    return 0;
}

int open_input_file_descriptor(command_t *command, char *comm)
{
    int size = 0;
    if (!comm) return 1;
    char *redirection_in = strchr(comm, '<');
    if (!redirection_in) return 1;
    char *redirection_in_word = strrchr(comm, '<');
    char *file = get_redirection_filename(redirection_in_word + 1, &size);
    if (file == NULL)
        return 1;
    if (command->redirect_in_word_wait) {
        command->in_fd = -69;
        command->awaited_word = file;
    } else {
        command->in_fd = open(file, O_RDONLY);
        free(file);
    }
    memset(redirection_in, ' ',
        size + (command->redirect_in_word_wait ? 2 : 1));
    return 0;
}

int get_redirections_file_descriptors(command_t *command, char *comm)
{
    if (command->redirect_out && open_output_file_descriptor(command, comm)) {
        return 1;
    }

    if (command->redirect_in && open_input_file_descriptor(command, comm)) {
        return 1;
    }

    return 0;
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
