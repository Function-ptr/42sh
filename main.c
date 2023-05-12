/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** MAIN
*/

#include "shell.h"
#include "history.h"

pid_t cpid1, cpid2;

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
    cpid1 = cpid2 = -1;
    signal(SIGINT, sighandler);
    init_history(environment);
    int status = shell(environment);
    clear_environment(environment);
    return (status);
}
