/*
** EPITECH PROJECT, 2023
** process_arrow_keys.c
** File description:
** process arrow keys
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

#include "line_edition.h"
#include "history.h"

bool process_arrow_keys(InputBuffer *input_data, ShellContext *context)
{
    if (input_data->read[2] == 'C') {
        if (input_data->cursor_pos >= input_data->input_len) return true;
        input_data->cursor_pos += utf8_char_len
            (input_data->input[input_data->cursor_pos + 1]);
        printf("\x1b[C");
        return true;
    }
    if (input_data->read[2] == 'D') {
        if (input_data->cursor_pos <= 0) return true;
        uint8_t prev_len = previous_utf8_char_length(input_data->input,
            input_data->cursor_pos);
        if (prev_len > input_data->cursor_pos)
            return true;
        input_data->cursor_pos -= prev_len == 1 ? 1 : prev_len;
        printf("\x1b[D");
        return true;
    }
    if (input_data->read[2] == 'A') {
        if (context->env->history->len_file +
        context->env->history->len_session_history <= 0)
            return true;
        static uint16_t current_history_offset = 1;
        if (current_history_offset > context->env->history->len_file +
        context->env->history->len_session_history)
            return true;
        input_data->input_dup = strdup(input_data->input);
        if (!input_data->input_dup)
            input_data->input_dup = input_data->input_len == 0 ? calloc(1, 1) :
                strdup(input_data->input);
        char *history_line = history_get_line_from_offset(context->env->history,
            current_history_offset); history_line[strlen(history_line) - 1] = 0;
        if ((int)fastlog2((float)strlen(history_line)) >=
            (int)(fastlog2(input_data->input_len) + 0.5f))
            realloc_input(input_data);
        printf("\x1b[%dD\x1b[K", input_data->cursor_pos);
        input_data->input = strdup(history_line);
        input_data->input_len = strlen(history_line);
        input_data->cursor_pos = input_data->input_len;
        printf("%s", input_data->input);
        current_history_offset++;
        return true;
    }
    return false;
}

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
