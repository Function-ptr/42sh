/*
** EPITECH PROJECT, 2023
** header
** File description:
** header
*/

#include "linked_lists.h"

void delete_element(node_t **head, char *str)
{
    node_t *current = *head;
    node_t *prev = NULL;

    if (current != NULL && strcmp(current->data_a, str) == 0) {
        *head = current->next;
        free(current->data_a);
        free(current->data_b);
        free(current);
        return;
    }
    while (current != NULL && strcmp(current->data_a, str) != 0) {
        prev = current;
        current = current->next;
    }
    if (current == NULL)
        return;
    prev->next = current->next;
    free(current->data_a);
    free(current->data_b);
    free(current);
}
