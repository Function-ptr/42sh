/*
** EPITECH PROJECT, 2023
** shell.c
** File description:
** shell for minishell1
*/

#include "shell.h"
#include "history.h"
#include "prompt.h"

int write_prompt(envdata_t *env)
{
    char *user = get_environment_variable(env->env, "USER");
    char *host = get_environment_variable(env->env, "HOSTNAME");
    if (env->is_fallback) {
        printf("\033[0m\033[93;1;5m> \033[0m"); return 1;
    }
    char *stat_icon = WIFSIGNALED(env->status) && env->status != 1 ? "⚡" :
            (env->status ? "×" : "λ");
    if (user && host)
        printf(STDPROMPT, user + 5, host + 9, env->cwd, stat_icon);
    if (user && !host)
        printf(ONEVALPROMPT, user + 5, env->cwd, stat_icon);
    if (!user && host)
        printf(ONEVALPROMPT, host + 9, env->cwd, stat_icon);
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
