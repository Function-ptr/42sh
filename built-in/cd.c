/*
** EPITECH PROJECT, 2023
** cd.c
** File description:
** cd command for minishell
*/

#include "minishell.h"

int change_dir(envdata_t *env, char *input)
{
    char *ndir = NULL; bool go_home = false;
    if (!my_strcmp(input, "cd")) {
        ndir = &(get_environment_variable(env->env, "HOME")[5]); go_home = true;
    } else
        ndir = &input[3];
    if (!go_home && (input[2] == '-' || input[3] == '-'))
        ndir = env->prevcwd;
    if (chdir(ndir) == -1) {
        int err = errno;
        char *errstr = strerror(err);
        write(2, ndir, my_strlen(ndir));
        write(2, ": ", 2); write(2, errstr, my_strlen(errstr));
        write(2, ".\n", 2); return (1);
    }
    my_memset(env->prevcwd, 300, 0);
    my_strcpy(env->prevcwd, env->cwd);
    my_memset(env->cwd, 300, 0);
    if (getcwd(env->cwd, 300) == NULL)
        exit_with_error(env);
    set_environment_variable(env->env, "PWD", env->cwd); return (0);
}
