/*
** EPITECH PROJECT, 2023
** environment.h
** File description:
** environment header
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

#ifndef INC_42SH_ENVIRONMENT_H
    #define INC_42SH_ENVIRONMENT_H

    #include "types.h"
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <unistd.h>


    ///////////////////
    /// Environment ///
    ///////////////////

    int compare_variable_name(char *var, char *name);
    char **get_environment(envvar_t **env);
    void set_value(envvar_t *var, char *varname, char *value);
    char *get_environment_variable(envvar_t **env, char *var);
    void set_environment_variable(envvar_t **env, char *var, char *newvar);
    char *get_variable_name(char *args);
    void reverse_environment_variables(envvar_t **begin);
    void clear_environment_variables(envvar_t **list);
    void add_environment_variable(envvar_t **env, char *var);
    void clear_environment(envdata_t *envdata);
    void duplicate_environment(char **env, envvar_t **list);
    void reverse_path_directories(pathdir_t **begin);
    pathdir_t **get_path_directories(char *path);
    char *get_path_variable(envvar_t **env);
    envdata_t *initialize_envdata(char **env);
    envdata_t *initialize_fallback_environment(void);


    /////////////
    /// Utils ///
    /////////////

    void free_history(history_t *history);
    void exit_with_error(envdata_t *env);

    ////////////
    /// PATH ///
    ////////////

    void clear_path_directories(pathdir_t **list);
    void add_path_directory(pathdir_t **pathdirs, char *dir, int len);

    /////////////////
    /// Variables ///
    /////////////////

    void add_var(variables_t *vars, char *name, char *value,
        command_t *command);
    void remove_var(variables_t *variables, char *name);
    void show_vars(variables_t *variables, command_t *command);
    char *get_var_value(variables_t *variables, char *name);
    variables_t *init_variables(void);
    void clean_variables(variables_t *variables);

    ///////////////
    /// Aliases ///
    ///////////////

    void add_alias(aliases_t *aliases, char *name, char *value,
        command_t *command);
    void remove_alias(aliases_t *aliases, char *alias);
    char *get_aliases_content(aliases_t *aliases, char *alias);
    void show_aliases(aliases_t *aliases, command_t *command);
    aliases_t *init_aliases(void);
    void clean_aliases(aliases_t *aliases);

#endif //INC_42SH_ENVIRONMENT_H

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
