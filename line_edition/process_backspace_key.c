/*
** EPITECH PROJECT, 2023
** process_backspace_key.c
** File description:
** process backspace key for char deletion
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

void process_backspace_key(InputBuffer *input_data)
{
    if (input_data->cursor_pos <= 0 || input_data->input_len <= 0 ||
    input_data->cursor_pos > input_data->input_len)
        return;
    uint8_t len = previous_utf8_char_length(input_data->input,
        input_data->cursor_pos);
    if (len > input_data->cursor_pos || input_data->cursor_pos - len < 0)
        return;
    if (input_data->cursor_pos >= len)
        len = previous_utf8_char_length(input_data->input,
        input_data->cursor_pos - previous_utf8_char_length(input_data->input,
                                                    input_data->cursor_pos));
    if (input_data->cursor_pos < input_data->input_len)
        memmove(input_data->input + input_data->cursor_pos - len,
            input_data->input + input_data->cursor_pos,
            (input_data->input_len - input_data->cursor_pos));
    for (uint8_t i = 0; i <= len; i++)
        input_data->input[input_data->input_len - i] = '\0';
    input_data->input_len -= len;
    input_data->cursor_pos -= len;
    printf("\x1B[D\x1B[P");
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
