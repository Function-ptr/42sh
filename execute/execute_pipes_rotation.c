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
#include "execute.h"

pid_t start_piped_command(command_t *command, int *exiting, envdata_t *env,
    int *builtin_status)
{
    *builtin_status = -1;
    if (!command->command || command->command[0] == 0) {
        free_command(command); return (-1);
    } if (load_redirections_for_command(command) == -1) return (-1);
    if (command->depth == Parentheses) {
        *builtin_status = run_parentheses_command(command, env); return -2;
    }
    char *bname = strdup(command->command);
    if (!strcmp(get_binary_name(bname), "exit")) *exiting = 1;
    if (is_a_builtin(get_binary_name(bname))) {
        *builtin_status = builtin_funcs(command, env);
        free(bname); return (-2);
    }
    char *path = get_binary_filename(get_binary_name(bname), env->path_dirs);
    if (!path) {
        free(bname);  return (-1);
    }
    pid_t program_pid = fork_and_run(path, command, env->env);
    free(bname);
    return (program_pid);
}

void wait_and_free_command(command_t *command, pathdir_t **pathdirs,
    int *status, pid_t pid)
{
    char *bname = strdup(command->command);
    char *filename = get_binary_filename(get_binary_name(bname), pathdirs);
    free(bname);
    int stat = monitor_program(pid, filename);
    if (status != NULL)
        *status = stat;
    free(filename);
}

void open_pipe(command_t *command)
{
    int fds[2];
    pipe(fds);
    command->out_fd = fds[1];
    command->pipe_in_fd = fds[0];
}

void process_command(int **data, command_t **commands, envdata_t *env,
    pid_t *first)
{
    int *i = data[0], *status = data[1], *exit_now = data[2];
    pid_t second;
    commands[*i + 1]->in_fd = commands[*i]->pipe_in_fd;
    if (!commands[*i]->pipe_out)
        return;
    if (commands[*i + 1]->pipe_out)
        open_pipe(commands[*i + 1]);
    *status = 0;
    *exit_now = 0;
    second = start_piped_command(commands[*i + 1], exit_now, env, status);
    if (*first != -2)
        wait_and_free_command(commands[*i], env->path_dirs, NULL, *first);
    free_command(commands[*i]);
    *first = second;
}

/*
 * Here an output PID of -1 is an error and -2 means a builtin was started
*/
int loop_over_pipes(command_t **commands, envdata_t *env, int **data)
{
    int *i = data[0], nb_commands = *data[1], *exiting = data[2], status = 0;
    int exit_now = 0, *pos_status_exit[3] = {i, &status, &exit_now};
    open_pipe(commands[*i]);
    pid_t first = start_piped_command(commands[*i], &exit_now, env, &status);
    if (first == -1)
        return (1);
    for (; *i < nb_commands - 1; *i += 1) {
        process_command(pos_status_exit, commands, env, &first);
        if (first == -1) {
            *i += 1;
            free_remaining_piped_commands(commands, nb_commands, i);
            return (status == -1) ? 1 : status;
        }
    }
    if (status != -2 && first != -2)
        wait_and_free_command(commands[*i], env->path_dirs, &status, first);
    free_command(commands[*i]);
    *exiting = exit_now;
    return status;
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
