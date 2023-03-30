/*
** EPITECH PROJECT, 2022
** my_rev_list.c
** File description:
** Reverse a linked list
*/

#include "include/mylist.h"
#include <stdlib.h>

void my_rev_list(linked_list_t **begin)
{
    linked_list_t *tmp = *begin;
    linked_list_t *prev = NULL;
    linked_list_t *next;

    while (tmp != NULL) {
        next = tmp->next;
        tmp->next = prev;
        prev = tmp;
        tmp = next;
    }
    *begin = prev;
}
