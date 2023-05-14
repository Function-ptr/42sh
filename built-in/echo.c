/*
** EPITECH PROJECT, 2023
** echo
** File description:
** echo
*/

#include "built_in.h"
#include "prompt.h"
#include "my.h"
#include "parsing.h"

int has_n_flag(char **command)
{
    char **args = my_str_to_word_array(*command, " \t");
    int alen = my_char_arraylen(args), has_flag = 0, s = 0;
    for (int i = 1; i < alen; i++) {
        int arglen = (int)strlen(args[i]);
        if (arglen != 2 || args[i][0] != '-') break;
        if (!strcmp(args[i], "-n")) has_flag = 1;
    }
    for (int i = 0; i < alen; i++)
        free(args[i]);
    free(args);
    if (has_flag) {
        char *flagpos = strstr(*command, "-n");
        memset(flagpos, ' ', 2);
        *command = remove_spaces_in_command(*command, 0, false, &s);
    }
    return has_flag;
}

int echo(command_t *command)
{
    int nquotes = 0, i = 5, nonew = has_n_flag(&(command->command));
    if (strlen(command->command) <= 5) {
        if (!nonew) dprintf(command->out_fd, "\n");
        return 0;
    }
    while (command->command[i]) {
        if (command->command[i] == '"' || command->command[i] == '\'') {
            nquotes++;
            i++;
        }
        while (command->command[i] == ' ' && command->command[i + 1] == ' '
        && (nquotes % 2 == 0)) i++;
        dprintf(command->out_fd, "%c", command->command[i]);
        i++;
    }
    if (!nonew) dprintf(command->out_fd, "\n");
    return 0;
}

int moai(command_t *command)
{
    dprintf(command->out_fd, MOAI);
    return 0;
}
