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

int alias(command_t *cmd, envdata_t *env)
{
    char *data_a = get_regex(cmd->command, "alias ([^=']+)=.*");
    char *data_b = get_regex(cmd->command, "alias [^=']+='([^']*)'");
    if (data_a == NULL || data_b == NULL) return 1;
    printf("%s\n%s\n", data_a, data_b);
    return 0;
}
