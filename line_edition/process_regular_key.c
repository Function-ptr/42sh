/*
** EPITECH PROJECT, 2023
** process_input.c
** File description:
** process_input file for 42sh
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
#include <ctype.h>

static bool add_key_at_end(InputBuffer *input_data, int8_t new_char_len)
{
    if (input_data->cursor_pos >= input_data->input_len) {
        memcpy(input_data->input + input_data->cursor_pos,
            input_data->read, new_char_len);
        input_data->input_len += new_char_len;
        input_data->cursor_pos += new_char_len;

        input_data->input[input_data->input_len] = '\0';
        if (input_data->is_tty)
            printf("%.*s", new_char_len, input_data->read);
        return true;
    }
    return false;
}

static bool insert_new_utf8_before_current_utf8(InputBuffer *input_data,
    int8_t new_char_len, int8_t current_char_len)
{
    if (current_char_len > 1 && new_char_len > 1) {
        memmove(input_data->input + input_data->cursor_pos + new_char_len - 1,
            input_data->input + input_data->cursor_pos - (current_char_len - 1),
            (input_data->input_len - input_data->cursor_pos) +
                                                    (current_char_len - 1));

        memcpy(
        input_data->input + input_data->cursor_pos - (current_char_len - 1),
        input_data->read, new_char_len);

        printf("\x1b[K%s",
        input_data->input + input_data->cursor_pos - (current_char_len - 1));

        input_data->input_len += new_char_len;
        input_data->cursor_pos += new_char_len;
        return true;
    }
    return false;
}

static void insert_new_char_before_current_char(InputBuffer *input_data,
    int8_t new_char_len, int8_t current_char_len)
{
    uint8_t offset = current_char_len > 1 ? 0 : new_char_len;

    memmove(input_data->input + input_data->cursor_pos + offset,
    input_data->input + input_data->cursor_pos - (current_char_len - 1),
    (input_data->input_len - input_data->cursor_pos) + (current_char_len - 1));

    memcpy(input_data->input + input_data->cursor_pos - (current_char_len - 1),
        input_data->read, new_char_len);

    printf("\x1b[K%s",
        input_data->input + input_data->cursor_pos - (current_char_len - 1));

    input_data->input_len += new_char_len;
    input_data->cursor_pos += new_char_len;
}

static void compute_and_move_cursor(InputBuffer *input_data)
{
    uint16_t i;
    i = input_data->input_len - 1;
    while (i >= input_data->cursor_pos) {
        int8_t c_len = utf8_char_len(input_data->input[i]);
        if (c_len <= 0)
            c_len = previous_utf8_char_length(input_data->input, i);
        i -= c_len;
        printf("\x1b[D");
    }
}

void process_regular_key(InputBuffer *input_data)
{
    if (iscntrl(input_data->read[0]) || !is_valid_utf8(input_data->read))
        return;
    int8_t new_char_len = utf8_char_len(input_data->read[0]);
    if (new_char_len == 1 && input_data->read_len > 1)
        new_char_len = input_data->read_len;
    if (add_key_at_end(input_data, new_char_len))
        return;
    int8_t current_char_len = utf8_char_len(
        input_data->input[input_data->cursor_pos]);
    if (current_char_len <= 0)
        current_char_len = previous_utf8_char_length(input_data->input,
            input_data->cursor_pos);
    if (!insert_new_utf8_before_current_utf8(input_data, new_char_len,
    current_char_len))
        insert_new_char_before_current_char(input_data, new_char_len,
            current_char_len);
    input_data->input[input_data->input_len] = '\0';
    compute_and_move_cursor(input_data);
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
