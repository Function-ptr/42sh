/*
** EPITECH PROJECT, 2022
** my_find_node.c
** File description:
** Find the 1st node containing the param
*/

#include "include/mylist.h"
#include <stdlib.h>

linked_list_t *my_find_node(linked_list_t const *begin, void const *data_ref,\
    int (*cmp)())
{
    const linked_list_t *tmp = begin;

    while (tmp != NULL) {
        if (!(*cmp)(tmp->data, data_ref)) {
            return ((linked_list_t *)tmp);
        }
        tmp = tmp->next;
    }
    return (0);
}
