/*
** EPITECH PROJECT, 2022
** my_params_to_list.c
** File description:
** convert program params to linked list
*/

#include <stdlib.h>
#include "include/mylist.h"
#include "include/printf.h"
#include <stdio.h>

void my_put_in_list(linked_list_t **list, const char *str)
{
    linked_list_t *element;
    element = malloc(sizeof(*element));
    element->data = (char *)str;
    element->next = *list;
    *list = element;
}

linked_list_t *my_params_to_list(int ac, char const **av)
{
    linked_list_t *list = NULL;

    for (int i = 0; i < ac; i++) {
        my_put_in_list(&list, av[i]);
    }
    return (list);
}

void my_show_ll(linked_list_t *list)
{
    linked_list_t *tmp;
    tmp = list;
    while (tmp != NULL) {
        my_putstr_do((tmp->data));
        my_putchar('\n');
        tmp = tmp->next;
    }
    return;
}
