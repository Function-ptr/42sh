/*
** EPITECH PROJECT, 2023
** header
** File description:
** header
*/

#include <stdlib.h>
#include <string.h>

#ifndef header
    #define header

// data_a -> string to replace
// data_b -> what to replace it with

typedef struct node {
    char *data_a;
    char *data_b;
    struct node *next;
} node_t;

#endif /* !header */
