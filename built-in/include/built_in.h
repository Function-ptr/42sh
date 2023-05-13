/*
** EPITECH PROJECT, 2023
** built-in.h
** File description:
** built-in header file for 42sh
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

#ifndef INC_42SH_BUILT_IN_H
    #define INC_42SH_BUILT_IN_H

    #include "types.h"
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <unistd.h>
    #include <errno.h>

    ////////////////
    /// Builtins ///
    ////////////////

    int builtin_funcs(command_t *cmd, envdata_t *env);
    void show_environment(envvar_t **env, command_t *command);
    int change_dir(envdata_t *env, char *input);
    void unset_env(envvar_t **env, char *inp, envdata_t *envdata);
    void set_env(envvar_t **env, command_t *command, envdata_t *envdata);
    int exit_with_status(command_t *command);
    int echo(command_t *command);
    bool is_a_builtin(char *binary);
    void show_history(history_t *history);
    void set_variable(command_t *command, variables_t *variables);
    void unset_variable(command_t *command, variables_t *variables);
    void unalias(command_t *command, aliases_t *aliases);
    void alias(command_t *command, aliases_t *aliases);
    int moai(command_t *command);
    int which(command_t *command, envdata_t *env);

    /////////////
    /// Utils ///
    /////////////

    void set_environment_variable(envvar_t **env, char *var, char *newvar);
    char *get_environment_variable(envvar_t **env, char *var);
    void exit_with_error(envdata_t *env);
    char *get_binary_name(char *str);
    int is_argv_long_enough(char *command, int cap);
    int compare_variable_name(char *var, char *name);
    void set_value(envvar_t *var, char *varname, char *value);
    char *get_variable_name(char *args);
    int my_str_isalphanum(char *str);


#endif //INC_42SH_BUILT_IN_H

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
