/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** MAIN
*/

#include "shell.h"
#include "history.h"

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
    init_history(environment);
    int status = shell(environment);
    dump_session_to_file(environment->history);
    clear_environment(environment);
    return (status);
}
