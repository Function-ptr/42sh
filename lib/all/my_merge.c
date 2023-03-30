/*
** EPITECH PROJECT, 2022
** my_merge.c
** File description:
** merge 2 linked lists
*/

#include <stdlib.h>
#include "include/mylist.h"
#include <stdio.h>


void my_merge(linked_list_t **begin1, linked_list_t *begin2, int (*cmp)())
{
    linked_list_t *tmp = begin2;
    while (tmp != NULL) {
        my_add_in_sorted_list(begin1, tmp->data, (*cmp));
        tmp = tmp->next;
    }
}
