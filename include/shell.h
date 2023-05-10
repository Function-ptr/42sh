/*
** EPITECH PROJECT, 2023
** minishell.h
** File description:
** minishell1
*/

#ifndef MINISHELL1_MINISHELL_H
    #define MINISHELL1_MINISHELL_H

    #include "types.h"
    #include <stdio.h>
    #include <unistd.h>
    #include <stdlib.h>
    #include <termios.h>

    /////////////
    /// Shell ///
    /////////////

    int shell(envdata_t *env, struct termios *old_term,
        struct termios *new_term);
    int array_len(char **arr);

    /////////////
    /// Utils ///
    /////////////

    void add_line_to_history(history_t *history, char *line);
    int run_user_input(char *input, envdata_t *env, bool *exiting);
    envdata_t *initialize_envdata(char **env);
    envdata_t *initialize_fallback_environment(void);
    void init_history(envdata_t *environment);
    void clear_environment(envdata_t *envdata);


#endif //MINISHELL1_MINISHELL_H
