/*
** EPITECH PROJECT, 2023
** line_edition_utils.c
** File description:
** line edition utilities functions
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

void realloc_input(InputBuffer *input_data)
{
    static uint8_t size_input = 10;
    size_t pow_size_input = 1 << size_input;

    if (input_data->read_len + input_data->input_len >= pow_size_input) {
        size_input++;
        pow_size_input = 1 << size_input;
        input_data->input = realloc(input_data->input, pow_size_input);
        memset(input_data->input + input_data->input_len, 0,
        (pow_size_input / 2 + 1));
    }
}

int8_t utf8_char_len(uint8_t byte)
{
    return (byte & 0x80) == 0x00 ? 1 :
        (byte & 0xE0) == 0xC0 ? 2 :
        (byte & 0xF0) == 0xE0 ? 3 :
        (byte & 0xF8) == 0xF0 ? 4 : -1;
}

uint8_t previous_utf8_char_length(const char* input, uint16_t cursor_position)
{
    uint8_t len = 1;

    for (uint8_t i = 0; i < 3 && (input[cursor_position] & 0xC0) == 0x80; ++i) {
        len++;
        if (cursor_position > 0)
            cursor_position--;
        else
            break;
    }
    return len;
}

bool is_valid_utf8(const char *s)
{
    uint8_t bytes_in_char = 0;
    unsigned char byte = (unsigned char)s[0];
    if (byte < 0x80) bytes_in_char = 1;
    if (byte >= 0x80 && byte < 0xC2) return false;
    if (byte >= 0xC2 && byte < 0xE0) bytes_in_char = 2;
    if (byte >= 0xE0 && byte < 0xF0) bytes_in_char = 3;
    if (byte >= 0xF0 && byte < 0xF5) bytes_in_char = 4;
    if (byte >= 0xF5) return false;
    for (uint8_t i = 1; i < bytes_in_char; ++i)
        if ((s[i] & 0xC0) != 0x80)
            return false;
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
