/*
** EPITECH PROJECT, 2023
** chose_builtin.c
** File description:
** chose builitin to run
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

#include "built_in.h"
#include "parsing.h"

void builtin_funcs_bis(char *binname, command_t *cmd, bool *found, int *status)
{
    if (strcmp(binname, "exit") == 0) {
        *status = exit_with_status(cmd); *found = true;
    } if (strcmp(binname, "echo") == 0) {
        *status = echo(cmd); *found = true;
    } if (!*found)
        fprintf(stderr, "%s: Command not found.\n", binname);
    if (cmd->out_fd != STDOUT_FILENO)
        close(cmd->out_fd);
    if (cmd->in_fd != STDIN_FILENO)
        close(cmd->in_fd);
}

void builtins_env(command_t *command, envdata_t *env, bool *found,
    char *binname)
{
    if (!strcmp(binname, "unset")) {
        unset_variable(command, env->variables); *found = true;
    } if (!strcmp(binname, "unalias")) {
        unalias(command, env->aliases); *found = true;
    } if (!strcmp(binname, "alias")) {
        alias(command, env->aliases); *found = true;
    } if (!strcmp(binname, "moai")) {
        moai(command); *found = true;
    } if (strcmp(binname, "history") == 0) {
        show_history(env->history); *found = true;
    } if (strcmp(binname, "setenv") == 0) {
        set_env(env->env, command, env); *found = true;
    } if (strcmp(binname, "env") == 0) {
        show_environment(env->env, command); *found = true;
    }
}

void builtins_env_bis(envdata_t *env, bool *found,
    char *binname)
{
    if (!strcmp(binname, "prompt_on")) env->starship_prompt = *found = true;
    if (!strcmp(binname, "prompt_off")) {
        env->starship_prompt = false; *found = true;
    }
}

void handle_set_case(command_t *command, envdata_t *env, bool *found)
{
    char *dup = strdup(command->command);
    char *binname = get_binary_name(dup);
    if (!strcmp(binname, "set")) {
        set_variable(command, env->variables);
        *found = true;
    }
    free(dup);
}

int builtin_funcs(command_t *cmd, envdata_t *env)
{
    bool found = false; handle_set_case(cmd, env, &found);
    char *clean_cmd = strdup_without_backslash(cmd->command);
    free(cmd->command);
    char *input = cmd->command = clean_cmd, *b = strdup(input);
    char *binname = get_binary_name(b);
    int status = 0;
    if (strcmp(binname, "cd") == 0) {
        status = change_dir(env, input); found = true;
    } if (strcmp(binname, "unsetenv") == 0) {
        unset_env(env->env, input, env); found = true;
    } if (!strcmp(binname, "which")) {
        status = which(cmd, env); found = true;
    } if (!strcmp(binname, "repeat")) {
        status = repeat(cmd, env); found = true;
    } if (!strcmp(binname, "where")) {
        status = where(cmd, env); found = true;
    } builtins_env(cmd, env, &found, binname);
    builtins_env_bis(env, &found, binname);
    builtin_funcs_bis(binname, cmd, &found, &status);
    free(b); return (status);
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
