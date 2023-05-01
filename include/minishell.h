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
int is_path(char *str);
int array_len(char **arr);


///////////////
/// History ///
///////////////

size_t get_file_nb_lines(char *filename);
void init_history(envdata_t *environment);
void free_history(history_t *history);
void add_line_to_history(history_t *history, char *line);
char *history_get_line_from_offset(history_t *history, size_t offset);

#endif //MINISHELL1_MINISHELL_H
