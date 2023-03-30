/*
** EPITECH PROJECT, 2022
** my_add_in_sorted_list.c
** File description:
** Insert an element in a sorted linked list
*/

#include "include/mylist.h"
#include <stdlib.h>
#include <stdio.h>



void my_add_in_sorted_list(linked_list_t **begin, void *data, int (*c)())
{
    linked_list_t *tmp = *begin;
    while (tmp->next != NULL) {
        if ((*c)(tmp->data, data) <= 0 && (*c)(tmp->next->data, data) >= 0) {
            my_put_in_list(&(tmp->next), data);
            return;
        }
        tmp = tmp->next;
    }
}
