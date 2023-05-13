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
    char *user = get_environment_variable(env->env, "USER");
    char *host = get_environment_variable(env->env, "HOSTNAME");
    if (env->is_fallback) {
        printf("> ");
        return 1;
    }
    if (user && host)
        printf("<%s@%s %s >$ ", user + 5, host + 9, env->cwd);
    if (user && !host)
        printf("<%s %s >$ ", user + 5, env->cwd);
    if (!user && host)
        printf("<%s %s >$ ", host + 9, env->cwd);
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
        operate_on_previous_command(&input, env->history);
        if (input[0] == '!') {
            free(input);
            continue;
        }
        add_line_to_history(env->history, input);
        run_precmd(env);
        status = run_user_input(input, env, &exiting);
        free(input);
        if (exiting) return (status);
    }
}
