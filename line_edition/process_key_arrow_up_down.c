/*
** EPITECH PROJECT, 2023
** process_key_arrow_up.c
** File description:
** process arrow keys up for history in line edition
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

static char* load_check_history(InputBuffer *input_data, history_t *history)
{
    if (input_data->history_offset <= 1)
        input_data->input_dup = input_data->input_len == 0 ? calloc(1, 1) :
            strdup(input_data->input);

    char *history_line = history_get_line_from_offset(history,
        input_data->history_offset);

    history_line[strlen(history_line) - 1] = 0;

    if ((int)fastlog2((float)strlen(history_line)) >=
    (int)(fastlog2(input_data->input_len) + 0.5))
        realloc_input(input_data);

    return history_line;
}

static void put_cursor_to_end_of_line(InputBuffer *input_data)
{
    while (input_data->cursor_pos < input_data->input_len) {
        int8_t c_len = utf8_char_len(input_data->input[input_data->cursor_pos]);

        if (c_len <= 0)
            c_len = previous_utf8_char_length(input_data->input,
                input_data->cursor_pos);

        input_data->cursor_pos += c_len;

        printf("\x1b[C");
    }
}

bool process_key_arrow_up(InputBuffer *input_data, history_t *history)
{
    int history_len = history->len_file +
        history->len_session_history;
    if (history_len <= 0)
        return true;
    if (input_data->history_offset > history_len)
        return true;

    char* history_line = load_check_history(input_data, history);
    put_cursor_to_end_of_line(input_data);
    if (input_data->cursor_pos > 0)
        printf("\x1b[%dD", input_data->cursor_pos);
    memset(input_data->input, 0, input_data->input_len);
    input_data->input = strcpy(input_data->input, history_line);
    input_data->input_len = input_data->cursor_pos = strlen(history_line);
    printf("\x1b[K%s", input_data->input);

    input_data->history_offset++;
    free(history_line);
    return true;
}

bool process_key_arrow_down(InputBuffer *input_data)
{
    if (input_data->history_offset <= 1)
        return true;
    put_cursor_to_end_of_line(input_data);
    if (input_data->cursor_pos > 0)
        printf("\x1b[%dD", input_data->cursor_pos);
    if (!(input_data->input_dup))
        input_data->input_dup = calloc(1, 1);
    input_data->input = strcpy(input_data->input, input_data->input_dup);
    input_data->input_len = input_data->cursor_pos =
        strlen(input_data->input_dup);
    free(input_data->input_dup);
    input_data->input_dup = NULL;
    printf("\x1b[K%s", input_data->input);
    input_data->history_offset = 1;
    return true;
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
