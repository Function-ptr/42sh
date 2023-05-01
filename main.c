/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** MAIN
*/

#include "minishell.h"

void open_history_file(envdata_t *environment)
{
    char *home = get_environment_variable(environment->env, "HOME");
    char *histpos = calloc(strlen(home) + 10, sizeof(char));
    strcpy(histpos, home + 5);
    strcat(histpos, "/.42sh_history");
    environment->history_fd = open(histpos, O_CREAT | O_APPEND |
        O_RDWR, S_IRUSR | S_IWUSR);
    free(histpos);
}

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
    open_history_file(environment);
    int status = shell(environment);
    clear_environment(environment);
    return (status);
}
