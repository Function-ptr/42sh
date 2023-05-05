/*
** EPITECH PROJECT, 2023
** header
** File description:
** header
*/

#include "built_in.h"

char *get_regex(char *src, char *exp)
{
    regex_t regex;
    regmatch_t match[2];
    int ret = regcomp(&regex, exp, REG_EXTENDED);
    if (ret) return NULL;
    ret = regexec(&regex, src, 2, match, 0);
    if (ret != 0) return NULL;
    int len = match[1].rm_eo - match[1].rm_so;
    char *res = malloc(sizeof(char) * (len + 1));
    strncpy(res, src + match[1].rm_so, len);
    res[len] = '\0';
    regfree(&regex);
    return res;
}

int show_alias(envdata_t *env)
{
    node_t *temp = env->aliases;
    while (temp != NULL) {
        printf("%s=%s\n", temp->data_a, temp->data_b);
        temp = temp->next;
    }
    return 0;
}

int alias(command_t *cmd, envdata_t *env)
{
    if (cmd->command[5] == '\0') return show_alias(env);
    char *data_a = get_regex(cmd->command,
    "alias[[:space:]]*['\"]?([^=[:space:]\'\"]+)['\"]?");
    char *data_b = get_regex(cmd->command, "alias [^=']+='([^']*)'");
    if (data_a == NULL && data_b == NULL) return 1;
    if (data_a == NULL) { free(data_b); return 1; };
    if (data_b == NULL) { free(data_a); return 1; };
    append(&env->aliases, data_a, data_b);
    free(data_a);
    free(data_b);
    return 0;
}

int unalias(command_t *cmd, envdata_t *env)
{
    if (cmd->command[7] == '\0') return 1;
    char *alias = cmd->command + 8;
    delete_element(&env->aliases, alias);
    return 0;
}
