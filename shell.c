/*
** EPITECH PROJECT, 2023
** shell.c
** File description:
** shell for minishell1
*/

#include "shell.h"
#include "history.h"

int write_prompt(envdata_t *env)
{
    if (!env->is_fallback) {
        printf("<%s@%s %s >$ ", env->user, env->hostname, env->cwd);
    } else
        printf("> ");
    return (1);
}

int shell(envdata_t *env)
{
    int status = 0, exiting = 0;
    while ((isatty(0) && write_prompt(env)) || 1) {
        size_t input_len = 1;
        char *input = NULL;
        if (getline(&input, &input_len, stdin) == -1) {
            free(input);
            return (status);
        }
        add_line_to_history(env->history, input);
        status = run_user_input(input, env, &exiting);
        free(input);
        if (exiting)
            return (status);
    }
}
