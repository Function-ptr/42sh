/*
** EPITECH PROJECT, 2023
** echo
** File description:
** echo
*/

#include "minishell.h"

int echo(command_t *command)
{
    int nquotes = 0;
    int i = 5;
    if (strlen(command->command) <= 5) {
        write(1, "\n", 1); return 0;
    }
    while (command->command[i]) {
        if (command->command[i] == '"' || command->command[i] == '\'') {
            nquotes++; i++;
        }
        while (command->command[i] == ' ' && command->command[i + 1] == ' '
        && (nquotes % 2 == 0)) i++;
        write(1, &command->command[i], 1);
        i++;
    }
    write(1, "\n", 1);
    return 0;
}
