/*
** EPITECH PROJECT, 2022
** my_sort_list.c
** File description:
** Sort a linked list
*/

#include "include/mylist.h"
#include <stdlib.h>
#include <stdio.h>

void my_sort_list(linked_list_t **begin, int (*cmp)())
{
    linked_list_t *tmp = *begin;
    if (tmp == NULL)
        return;
    while (tmp->next != NULL) {
        if ((*cmp)(tmp->data, tmp->next->data) > 0) {
            void *data;
            data = tmp->data;
            tmp->data = tmp->next->data;
            tmp->next->data = data;
            tmp = *begin;
        } else {
            tmp = tmp->next;
        }
    }
}
