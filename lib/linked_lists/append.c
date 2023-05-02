/*
** EPITECH PROJECT, 2023
** header
** File description:
** header
*/

#include "linked_lists.h"

void append(node_t **head, char *data_a, char *data_b)
{
    if (get_from_str(*head, data_a) != NULL) return;
    node_t *new_node = malloc(sizeof(node_t));
    node_t *last = *head;

    new_node->data_a = strdup(data_a);
    new_node->data_b = strdup(data_b);
    new_node->next = NULL;
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
}
