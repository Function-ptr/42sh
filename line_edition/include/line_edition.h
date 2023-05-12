/*
** EPITECH PROJECT, 2023
** line_edition.h
** File description:
** line_edition header file for 42sh
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

#ifndef INC_42SH_LINE_EDITION_H
    #define INC_42SH_LINE_EDITION_H

    #include <termios.h>
    #include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <stdint.h>
    #include <stdbool.h>
    #include "types.h"

    typedef struct {
        envdata_t *env;
        uint8_t status;
        bool exiting;
    } ShellContext;

    typedef struct {
        char input[4096];
        uint16_t input_len;
        uint16_t cursor_pos;
        char read[4];
        uint8_t read_len;
        bool is_tty;
    } InputBuffer;

    void configure_terminal(struct termios *new_term, struct termios *old_term);
    void restore_terminal(struct termios *old_term);
    int8_t utf8_char_len(uint8_t byte);
    uint8_t previous_utf8_char_length(const char* input,
        uint16_t cursor_position);
    bool process_arrow_keys(InputBuffer *input_data);
    void process_backspace_key(InputBuffer *input_data);
    bool process_delete_key(InputBuffer *input_data);
    void process_enter_key(ShellContext *context, InputBuffer *input_data);
    bool process_home_end_keys(InputBuffer *input_data);
    void process_regular_key(InputBuffer *input_data);
    void operate_on_previous_command(char *input, history_t *history);
    void add_line_to_history(history_t *history, char *line);
    int run_user_input(char *input, envdata_t *env, bool *exiting);
    uint8_t write_prompt(envdata_t *env);
    bool is_valid_utf8(const char *s);
    void handle_ctrl_d(ShellContext *context, InputBuffer *input_data);

#endif //INC_42SH_LINE_EDITION_H

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
