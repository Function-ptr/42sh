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
        int exiting;
    } ShellContext;

    typedef struct {
        char *input;
        char *input_dup;
        uint16_t input_len;
        uint16_t cursor_pos;
        char read[5];
        uint8_t read_len;
        uint16_t history_offset;
        bool is_tty;
    } InputBuffer;

    void configure_terminal(struct termios *new_term, struct termios *old_term);
    void restore_terminal(struct termios *old_term);
    int8_t utf8_char_len(uint8_t byte);
    uint8_t previous_utf8_char_length(const char* input,
        uint16_t cursor_position);
    bool process_arrow_keys(InputBuffer *input_data, ShellContext *context);
    void process_backspace_key(InputBuffer *input_data);
    bool process_delete_key(InputBuffer *input_data);
    void process_enter_key(ShellContext *context, InputBuffer *input_data);
    bool process_home_end_keys(InputBuffer *input_data);
    void process_regular_key(InputBuffer *input_data);
    void operate_on_previous_command(char *input, history_t *history);
    void add_line_to_history(history_t *history, char *line);
    int run_user_input(char *input, envdata_t *env, int *exiting);
    void write_prompt(envdata_t *env);
    bool is_valid_utf8(const char *s);
    void handle_ctrl_d(ShellContext *context);
    bool process_key_arrow_up(InputBuffer *input_data, history_t *history);
    void realloc_input(InputBuffer *input_data);
    bool process_key_arrow_down(InputBuffer *input_data);
    char* get_last_word(const char* str);
    char* auto_complete_dir(const char* path);
    char *autocomplete_from_path(char *input, envdata_t *env);
    void process_tab_key(InputBuffer *input_data, ShellContext *context);

static inline float fastlog2 (float x)
{
    union {float f; uint32_t i;} xv = {x}, lv, mx;
    mx.i = 0x3f000000u | (xv.i & 0x007FFFFFu);
    lv.i = 0x43800000u | (xv.i >> 8u);

    return lv.f - 380.22544f
        - 1.498030302f * mx.f
        - 1.72587999f / (0.3520887068f + mx.f);
}


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
