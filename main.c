/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** MAIN
*/

#include "shell.h"
#include "history.h"
#include "line_edition.h"
#include "environment.h"

pid_t cpid1, cpid2;

int main(int ac, __attribute__((unused)) char **av, char **env)
{
    if (env == NULL || ac != 1)
        return (84);
    envdata_t *environment;
    if (*env != NULL)
        environment = initialize_envdata(env);
    else
        environment = initialize_fallback_environment();
    if (environment == NULL)
        return (84);
    struct termios old_term, new_term;
    cpid1 = cpid2 = -1;
    signal(SIGINT, sighandler);
    init_history(environment);
    environment->variables = init_variables();
    environment->aliases = init_aliases();
    int status = shell(environment, &old_term, &new_term);
    clear_environment(environment);
    restore_terminal(&old_term);
    return (status);
}
