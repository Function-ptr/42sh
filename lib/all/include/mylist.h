/*
** EPITECH PROJECT, 2022
** mylist.h
** File description:
** linked list
*/

#ifndef LINK_LIST_H_

    #define LINK_LIST_H_
typedef struct linked_list {
    void *data;
    struct linked_list *next;
} linked_list_t;

void my_add_in_sorted_list(linked_list_t **begin, void *data, int (*c)());

int my_apply_on_matching_nodes(linked_list_t *begin, void const *data_ref,\
    int (*f)(), int (*cmp)());

int my_apply_on_nodes(linked_list_t *begin, int (*f)(void *));

void my_concat_list(linked_list_t **begin1, linked_list_t *begin2);

void delete_node(linked_list_t **begin, linked_list_t *prev,\
    linked_list_t *curr);

int my_delete_nodes(linked_list_t **begin, void const *data_ref, int (*cmp)());

linked_list_t *my_find_node(linked_list_t const *begin, void const *data_ref,\
    int (*cmp)());

int my_list_size(linked_list_t const *begin);

void my_merge(linked_list_t **begin1, linked_list_t *begin2, int (*cmp)());

linked_list_t *my_params_to_list(int ac, char const **av);

void my_show_ll(linked_list_t *list);

void my_put_in_list(linked_list_t **list, const char *str);

void my_rev_list(linked_list_t **begin);

void my_sort_list(linked_list_t **begin, int (*cmp)());


#endif
