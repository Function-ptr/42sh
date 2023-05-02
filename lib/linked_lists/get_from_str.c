/*
** EPITECH PROJECT, 2023
** header
** File description:
** header
*/

// la fonction prendra en paramètre une liste chainée et une string,
// et renverra le str remplacé de la liste chainée correspondante

#include "include/linked_lists.h"

char *get_from_str(node_t *head, char *str)
{
    node_t *current = head;

    while (current != NULL) {
        if (strcmp(current->data_a, str) == 0)
            return (current->data_b);
        current = current->next;
    }
    return (NULL);
}
