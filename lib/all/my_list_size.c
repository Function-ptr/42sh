/*
** EPITECH PROJECT, 2022
** my_list_size.c
** File description:
** Returns the length of a linked list
*/

#include "include/mylist.h"
#include <stdlib.h>

int my_list_size(linked_list_t const *begin)
{
    const linked_list_t *tmp;
    tmp = begin;
    int size = 0;
    while (tmp != NULL) {
        size++;
        tmp = tmp->next;
    }
    return (size);
}
