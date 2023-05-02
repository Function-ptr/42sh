/*
** EPITECH PROJECT, 2023
** header
** File description:
** header
*/

#include "linked_lists.h"

void free_list(node_t **head)
{
    node_t *current = *head;
    node_t *next;

    while (current != NULL) {
        next = current->next;
        free(current->data_a);
        free(current->data_b);
        free(current);
        current = next;
    }
    *head = NULL;
}
