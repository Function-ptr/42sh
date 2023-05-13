/*
** EPITECH PROJECT, 2023
** echo
** File description:
** echo
*/

#include "built_in.h"
#include "prompt.h"

int echo(command_t *command)
{
    int nquotes = 0, i = 5;
    if (strlen(command->command) <= 5) {
        dprintf(command->out_fd, "\n");
        return 0;
    }
    while (command->command[i]) {
        if (command->command[i] == '"' || command->command[i] == '\'') {
            nquotes++;
            i++;
        }
        while (command->command[i] == ' ' && command->command[i + 1] == ' '
        && (nquotes % 2 == 0))
            i++;
        dprintf(command->out_fd, "%c", command->command[i]);
        i++;
    }
    dprintf(command->out_fd, "\n");
    return 0;
}

int moai(command_t *command)
{
    dprintf(command->out_fd, MOAI);
    return 0;
}
