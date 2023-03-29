/*
** EPITECH PROJECT, 2023
** my.h
** File description:
** header file for 42sh
*/

#ifndef MINISHELL1_MY_H
    #define MINISHELL1_MY_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <dirent.h>
    #include <signal.h>
    #include <stdbool.h>

    typedef struct {
        char *name;
        char *value;
    } env_t;

    typedef struct linked_list {
        env_t *var;
        struct linked_list *next;
    } ll_t;

    typedef struct command {
        bool pipe_in;       // is input piped (incompatible with redirect_in)
        bool pipe_out;      // is output piped (incompatible with redirect_out)
        bool redirect_in;   // is input redirected ( < )
        bool redirect_in_word_wait; // is input redirected with a word_wait ( << )
        bool redirect_out;  // is output redirected ( > )
        bool redirect_out_append; // is output redirected with append ( >> )
        char *command;      // command string
        char next_separator; // next separator ->  "| ; \0"
        int in_fd;          // input file descriptor (default 0)
        int out_fd;         // output file descriptor (default 1)
        int pipe_in_fd;     // file descriptor for input pipe
    } command_t;

#endif //MINISHELL1_MY_H
