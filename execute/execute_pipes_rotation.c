/*
** EPITECH PROJECT, 2023
** execute_pipes_rotation.c
** File description:
** Execute rotation for infinite pipes and avoid buffer blocking
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
#include "minishell.h"

char *get_binary_filename(char *command, pathdir_t **pathdirs)
{
    char *cmd = strdup(command);
    if (strchr(cmd, '/') != NULL) {
        if (!access(cmd, F_OK))
            return (cmd);
        else {
            write(2, cmd, strlen(cmd));
            write(2, ": Command not found.\n", 21);
            free(cmd);
            return (NULL);
        }
    }
    return get_command_in_path(cmd, pathdirs);
}

pid_t start_piped_command(command_t *command, int *exiting, envdata_t *env,
    int *builtin_status)
{
    *builtin_status = -1;
    if (!command->command || command->command[0] == 0) {
        free_command(command);
        return (-1);
    }
    if (load_redirections_for_command(command) == -1)
        return (-1);
    char *bname = my_strdup(command->command);
    if (!my_strcmp(get_binary_name(bname), "exit"))
        *exiting = 1;
    if (is_a_builtin(get_binary_name(bname))) {
        *builtin_status = builtin_funcs(command, env);
        free(bname);
        return (-2);
    }
    char *path = get_binary_filename(command->command, env->path_dirs);
    pid_t program_pid = fork_and_run(path, command, env->env);
    free(bname);
    return (program_pid);
}

int loop_over_pipes(command_t **commands, envdata_t *env, int **data)
{
    int *i = data[0], nb_commands = *data[1], *exiting = data[2], status = 0;
    int fds[2], exit_now = 0;
    pipe(fds);
    commands[*i]->out_fd = fds[1];
    commands[*i]->pipe_in_fd = fds[0];
    pid_t first = start_piped_command(commands[*i], &exit_now, env, &status);
    char *filename;
    if (first == -1)
        return (1);
    pid_t second;
    while (*i < nb_commands - 1) {
        memset(fds, 0, 8);
        commands[*i + 1]->in_fd = commands[*i]->pipe_in_fd;
        if (!commands[*i]->pipe_out)
            break;
        if (commands[*i + 1]->pipe_out) {
            pipe(fds);
            commands[*i + 1]->out_fd = fds[1];
            commands[*i + 1]->pipe_in_fd = fds[0];
        }
        status = 0;
        exit_now = 0;
        second = start_piped_command(commands[*i + 1], &exit_now, env, &status);
        if (second == -1) {
            for (; *i < nb_commands - 1 && commands[*i]->pipe_out; *i += 1)
                free_command(commands[*i]);
            free(commands[*i]);
            return status;
        }
        if (first != -2) {
            filename = get_binary_filename(commands[*i]->command,
                env->path_dirs);
            monitor_program(first, filename);
            free(filename);
            free_command(commands[*i]);
        }
        first = second;
        *i += 1;
    }
    if (status != -2 && first != -2) {
        filename = get_binary_filename(commands[*i]->command, env->path_dirs);
        status = monitor_program(first, filename);
        free(filename);
    }
    *exiting = exit_now;
    return status;
}

int pipe_rotation(command_t **commands, envdata_t *env, int *exiting,
    int nb_commands)
{
    int final_status = 0, i = 0;
    int *data[3] = {&i, &nb_commands, exiting};
    for (; i < nb_commands; i++) {
        final_status = 0;
        if (!commands[i]->pipe_out)
            final_status = run_command(commands[i], exiting, env);
        else
            final_status = loop_over_pipes(commands, env, data);
        if (final_status == -1)
            return (-1);
    }
    return final_status;
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
