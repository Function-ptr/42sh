/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** MAIN
*/

#include "shell.h"
#include "history.h"
#include "line_edition.h"

int main(int ac, char **av, char **env)
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
    init_history(environment);
    int status = shell(environment, &old_term, &new_term);
    clear_environment(environment);
    restore_terminal(&old_term);
    return (status);
}
