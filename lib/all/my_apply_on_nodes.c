/*
** EPITECH PROJECT, 2022
** my_apply_on_nodes.c
** File description:
** Applies a given function to all data
*/

#include <stdlib.h>
#include "include/mylist.h"
#include <stdio.h>

int my_apply_on_nodes(linked_list_t *begin, int (*f)(void *))
{
    linked_list_t *tmp;
    tmp = begin;
    while (tmp != NULL) {
        (*f)(tmp->data);
        tmp = tmp->next;
    }
    return (0);
}
