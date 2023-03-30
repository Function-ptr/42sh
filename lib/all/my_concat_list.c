/*
** EPITECH PROJECT, 2022
** my_concat_list.c
** File description:
** Concatenate 2 linked lists
*/

#include <stdlib.h>
#include "include/mylist.h"

void my_concat_list(linked_list_t **begin1, linked_list_t *begin2)
{
    linked_list_t *tmp = *begin1;
    linked_list_t *prev;

    while (tmp != NULL) {
        prev = tmp;
        tmp = tmp->next;
    }
    prev->next = begin2;
}
