/*
** EPITECH PROJECT, 2023
** minishell.h
** File description:
** minishell1
*/

#ifndef MINISHELL1_MINISHELL_H
    #define MINISHELL1_MINISHELL_H
        #include <unistd.h>
        #include <stdio.h>
        #include <stdlib.h>
        #include <fcntl.h>
        #include <time.h>
        #include <string.h>
        #include <signal.h>
        #include <stddef.h>
        #include <sys/stat.h>
        #include <sys/types.h>
        #include <dirent.h>
        #include <sys/wait.h>
        #include "my.h"
        #include "printf.h"
        #include <errno.h>


///////////////
/// General ///
///////////////

int shell(envdata_t *env);
int is_argv_long_enough(char *command, int cap, char *func);
int is_path(char *str);
int array_len(char **arr);

////////////////
/// Builtins ///
////////////////

int builtin_funcs(command_t *cmd, envdata_t *env);
void show_environment(envvar_t **env, command_t *command);
int change_dir(envdata_t *env, char *input);
void unset_env(envvar_t **env, char *inp);
void set_env(envvar_t **env, command_t *command);
int exit_with_status(command_t *command);
int echo(command_t *command);
bool is_a_builtin(char *binary);








///////////////
/// History ///
///////////////

size_t get_file_nb_lines(char *filename);
void init_history(envdata_t *environment);
void free_history(history_t *history);
void add_line_to_history(history_t *history, char *line);
char *history_get_line_from_offset(history_t *history, size_t offset);

#endif //MINISHELL1_MINISHELL_H
