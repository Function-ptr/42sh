/*
** EPITECH PROJECT, 2022
** my_apply_on_nodes.c
** File description:
** Applies a given function to all data
*/

#include <stdlib.h>
#include "include/mylist.h"
#include <stdio.h>

int my_apply_on_matching_nodes(linked_list_t *begin, void const *data_ref,\
    int (*f)(), int (*cmp)())
{
    linked_list_t *tmp = begin;
    while (tmp != NULL) {
        if (!(*cmp)(tmp->data, data_ref)) {
            (*f)(tmp->data);
        }
        tmp = tmp->next;
    }
    return (0);
}
