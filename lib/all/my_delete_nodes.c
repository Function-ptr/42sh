/*
** EPITECH PROJECT, 2022
** my_delete_nodes.c
** File description:
** Remove all nodes eq to the value
*/

#include "include/mylist.h"
#include <stdlib.h>

void delete_node(linked_list_t **begin, linked_list_t *prev,\
    linked_list_t *curr)
{
    if (prev == NULL) {
        *begin = curr->next;
    } else {
        prev->next = curr->next;
    }
}

int my_delete_nodes(linked_list_t **begin, void const *data_ref,\
    int (*cmp)())
{
    linked_list_t *tmp = *begin;
    linked_list_t *prev = NULL;

    while (tmp != NULL) {
        if (!(*cmp)(tmp->data, data_ref)) {
            delete_node(begin, prev, tmp);
        }
        prev = tmp;
        tmp = tmp->next;
    }

    return (0);
}
