/*
** EPITECH PROJECT, 2023
** types.h
** File description:
** data structures for 42sh
*/
/*
 _____               __      __
|  __ \              \ \    / /
| |__) |  __ _  ___   \ \  / /   ___   __ _   __ _  _ __
|  ___/  / _` |/ __|   \ \/ /   / _ \ / _` | / _` || '_ \
| |     | (_| |\__ \    \  /   |  __/| (_| || (_| || | | |
|_|      \__,_||___/     \/     \___| \__, | \__,_||_| |_|
                                       __/ |
                                      |___/
*/

#ifndef INC_42SH_TYPES_H
    #define INC_42SH_TYPES_H

    #include <stdbool.h>

    typedef unsigned long size_t;

    typedef enum {
        None,
        AND,
        OR
    } conditional_separation;

    typedef enum {
        Curr_shell,
        Parentheses,
        Backticks
    } exec_depth;

    typedef struct envvar {
        char *var;
        struct envvar *next;
    } envvar_t;

    typedef struct path_dir {
        char *dir;
        struct path_dir *next;
    } pathdir_t;

    typedef struct {
        char *line;
        long time;
    } history_entry_t;

    typedef struct {
        char *filename;
        int history_fd;
        history_entry_t *session_history;
        size_t len_session_history;
        size_t len_file;
        size_t current_pos; // 0 > LONG_MAX (positive offset)
    } history_t;

    typedef struct env_data {
        char is_fallback;
        envvar_t **env;
        char *path;
        pathdir_t **path_dirs;
        char *cwd;
        char *prevcwd;
        char *user;
        size_t userlen;
        char *hostname;
        size_t hostlen;
        history_t *history;
    } envdata_t;

    typedef struct command {
        bool pipe_in;       // is input piped (incompatible with redirect_in)
        bool pipe_out;      // is output piped (incompatible with redirect_out)
        bool redirect_in;   // is input redirected ( < )
        bool redirect_in_word_wait; // is input redirected with a word_wait (<<)
        char *awaited_word; // The word marking the end of input with <<
        bool redirect_out;  // is output redirected ( > )
        bool redirect_out_append; // is output redirected with append ( >> )
        char *command;      // command string
        char next_separator[2]; // next separator ->  "| ; \0 && ||"
        conditional_separation condition;
        exec_depth depth;   // is a normal command or has () or ``
        int in_fd;          // input file descriptor (default 0)
        int out_fd;         // output file descriptor (default 1)
        int pipe_in_fd;     // file descriptor for input pipe
    } command_t;

#endif //INC_42SH_TYPES_H


/*
─▄▀▀▀▀▄─█──█────▄▀▀█─▄▀▀▀▀▄─█▀▀▄
─█────█─█──█────█────█────█─█──█
─█────█─█▀▀█────█─▄▄─█────█─█──█
─▀▄▄▄▄▀─█──█────▀▄▄█─▀▄▄▄▄▀─█▄▄▀

─────────▄██████▀▀▀▀▀▀▄
─────▄█████████▄───────▀▀▄▄
──▄█████████████───────────▀▀▄
▄██████████████─▄▀───▀▄─▀▄▄▄──▀▄
███████████████──▄▀─▀▄▄▄▄▄▄────█
█████████████████▀█──▄█▄▄▄──────█
███████████──█▀█──▀▄─█─█─█───────█
████████████████───▀█─▀██▄▄──────█
█████████████████──▄─▀█▄─────▄───█
█████████████████▀███▀▀─▀▄────█──█
████████████████──────────█──▄▀──█
████████████████▄▀▀▀▀▀▀▄──█──────█
████████████████▀▀▀▀▀▀▀▄──█──────█
▀████████████████▀▀▀▀▀▀──────────█
──███████████████▀▀─────█──────▄▀
──▀█████████████────────█────▄▀
────▀████████████▄───▄▄█▀─▄█▀
──────▀████████████▀▀▀──▄███
──────████████████████████─█
─────████████████████████──█
────████████████████████───█
────██████████████████─────█
────██████████████████─────█
────██████████████████─────█
────██████████████████─────█
────██████████████████▄▄▄▄▄█

─────────────█─────█─█──█─█───█
─────────────█─────█─█──█─▀█─█▀
─────────────█─▄█▄─█─█▀▀█──▀█▀
─────────────██▀─▀██─█──█───█
*/
