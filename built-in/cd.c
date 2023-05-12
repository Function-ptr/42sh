/*
** EPITECH PROJECT, 2023
** cd.c
** File description:
** cd command for minishell
*/
#include "environment.h"
#include "built_in.h"
#include "execute.h"

void run_cwdcmd(envdata_t *env)
{
    char *cmd = get_var_value(env->variables, "cwdcmd");
    if (!cmd) return;
    int exiting = 0;
    run_user_input(cmd, env, &exiting);
}

int change_dir(envdata_t *env, char *input)
{
    char *ndir = NULL; bool go_home = false;
    if (!strcmp(input, "cd")) {
        ndir = &(get_environment_variable(env->env, "HOME")[5]);
        go_home = true;
    } else
        ndir = &input[3];
    if (!go_home && (input[2] == '-' || input[3] == '-')) ndir = env->prevcwd;
    run_cwdcmd(env);
    if (chdir(ndir) == -1) {
        int err = errno;
        fprintf(stderr, "%s: %s.\n", ndir, strerror(err));
        return (1);
    }
    memset(env->prevcwd, 0,300);
    strcpy(env->prevcwd, env->cwd);
    memset(env->cwd, 0, 300);
    if (getcwd(env->cwd, 300) == NULL) exit_with_error(env);
    set_environment_variable(env->env, "PWD", env->cwd); return (0);
}
