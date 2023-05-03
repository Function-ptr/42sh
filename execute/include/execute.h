/*
** EPITECH PROJECT, 2023
** execute.h
** File description:
** execute header file for 42sh
*/
/*
 _____               __      __
|  __ \              \ \    / /
| |__) |  __ _  ___   \ \  / /   ___   __ _   __ _  _ __
|  ___/  / _` |/ __|   \ \/ /   / _ \ / _` | / _` || '_ \
| |     | (_| |\__ \    \  /   |  __/| (_| || (_| || | | |
|_|      \__,_||___/     \/     \___| \__, | \__,_||_| |_|
                                       __/ |
                                      |___/
*/

#ifndef INC_42SH_EXECUTE_H
    #define INC_42SH_EXECUTE_H

    #include "types.h"
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <unistd.h>

    ////////////////////////
    /// Execute binaries ///
    ////////////////////////

    int check_exit_status(int status);
    int detect_command_type_and_run(command_t *command, int *exiting,
        envdata_t *env);
    int run_user_input(char *input, envdata_t *env, int *exiting);
    int run_command(command_t *command, int *exiting, envdata_t *env);
    pid_t fork_and_run(char *filepath, command_t *command, envvar_t **env);
    char *get_command_in_path(char *command, pathdir_t **path_dirs);
    int monitor_program(pid_t child_pid, char *filepath);
    char *get_binary_filename(char *command, pathdir_t **pathdirs);
    int loop_over_pipes(command_t **commands, envdata_t *env, int **data);

    /////////////
    /// Utils ///
    /////////////

    char *get_binary_name(char *str);
    bool is_a_builtin(char *binary);
    int builtin_funcs(command_t *cmd, envdata_t *env);
    void execution_error(char *command);
    char **get_environment(envvar_t **env);
    char **my_str_to_word_array(char const *str, char *sep);
    void free_command(command_t *command);
    int load_redirections_for_command(command_t *command);
    void free_remaining_piped_commands(command_t **commands, int nb_commands,
        int *i);
    command_t **cut_input_to_commands(char *input);


#endif //INC_42SH_EXECUTE_H

/*
─▄▀▀▀▀▄─█──█────▄▀▀█─▄▀▀▀▀▄─█▀▀▄
─█────█─█──█────█────█────█─█──█
─█────█─█▀▀█────█─▄▄─█────█─█──█
─▀▄▄▄▄▀─█──█────▀▄▄█─▀▄▄▄▄▀─█▄▄▀

─────────▄██████▀▀▀▀▀▀▄
─────▄█████████▄───────▀▀▄▄
──▄█████████████───────────▀▀▄
▄██████████████─▄▀───▀▄─▀▄▄▄──▀▄
███████████████──▄▀─▀▄▄▄▄▄▄────█
█████████████████▀█──▄█▄▄▄──────█
███████████──█▀█──▀▄─█─█─█───────█
████████████████───▀█─▀██▄▄──────█
█████████████████──▄─▀█▄─────▄───█
█████████████████▀███▀▀─▀▄────█──█
████████████████──────────█──▄▀──█
████████████████▄▀▀▀▀▀▀▄──█──────█
████████████████▀▀▀▀▀▀▀▄──█──────█
▀████████████████▀▀▀▀▀▀──────────█
──███████████████▀▀─────█──────▄▀
──▀█████████████────────█────▄▀
────▀████████████▄───▄▄█▀─▄█▀
──────▀████████████▀▀▀──▄███
──────████████████████████─█
─────████████████████████──█
────████████████████████───█
────██████████████████─────█
────██████████████████─────█
────██████████████████─────█
────██████████████████─────█
────██████████████████▄▄▄▄▄█

─────────────█─────█─█──█─█───█
─────────────█─────█─█──█─▀█─█▀
─────────────█─▄█▄─█─█▀▀█──▀█▀
─────────────██▀─▀██─█──█───█
*/
