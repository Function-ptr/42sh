/*
** EPITECH PROJECT, 2023
** process_tab_key.c
** File description:
** process tab key to autocomplete
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

bool is_only_spaces(const char* str)
{
    while (*str != '\0') {
        if (!isspace((unsigned char)*str)) {
            return false;
        }
        str++;
    }
    return true;
}

static void add_result_to_input(char* autocomplete,
    InputBuffer *input_data)
{
    int i = 0;
    while (autocomplete[i] != '\0') {
        input_data->input[input_data->cursor_pos] = autocomplete[i];
        input_data->cursor_pos++;
        i++;
    }
    input_data->input[input_data->cursor_pos] = '\0';
    input_data->input_len = strlen(input_data->input);
    input_data->cursor_pos = input_data->input_len;
    printf("%s", autocomplete);
}

void process_tab_key(InputBuffer *input_data, ShellContext *context)
{
    if (input_data->input_len == 0 || input_data->input_len !=
    input_data->cursor_pos || is_only_spaces(input_data->input))
        return;
    char *last_word = get_last_word(input_data->input);
    if (last_word == NULL) return;
    char *autocomplete = auto_complete_dir(last_word);
    if (autocomplete == NULL)
        autocomplete = autocomplete_from_path(last_word, context->env);
    if (autocomplete == NULL)
        autocomplete = autocomplete_from_history(last_word,
                                                    context->env->history);
    if (autocomplete != NULL)
        add_result_to_input(autocomplete, input_data);
    free(autocomplete);
    free(last_word);
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
