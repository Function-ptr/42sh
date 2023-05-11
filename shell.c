/*
** EPITECH PROJECT, 2023
** shell.c
** File description:
** shell for minishell1
*/

#include "shell.h"
#include "history.h"
#include "line_edition.h"
#include <locale.h>
#include <stdint.h>
#include <stdio.h>

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

uint8_t write_prompt(envdata_t *env)
{
    printf(env->is_fallback ? "> " : "<%s@%s %s >$ ", env->user,
        env->hostname, env->cwd);
    fflush(stdout);
    return 1;
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

bool process_arrow_keys(InputBuffer *input_data)
{
    if (input_data->read[2] == 'C' && input_data->cursor_pos <
        input_data->input_len) {
        input_data->cursor_pos += utf8_char_len
            (input_data->input[input_data->cursor_pos + 1]);
        printf("\x1b[C");
        return true;
    }
    if (input_data->read[2] == 'D' && input_data->cursor_pos > 0) {
        uint8_t prev_len = previous_utf8_char_length(input_data->input,
            input_data->cursor_pos);
        if (prev_len > input_data->cursor_pos)
            return true;
        input_data->cursor_pos -= prev_len == 1 ? 1 : prev_len;
        printf("\x1b[D");
        return true;
    }
    return false;
}

bool process_delete_key(InputBuffer *input_data)
{
    if (input_data->read[2] == '3' && input_data->read[3] == '~' &&
    input_data->cursor_pos < input_data->input_len) {
        int8_t len = utf8_char_len(input_data->input[input_data->cursor_pos]);
        memmove(input_data->input + input_data->cursor_pos,
                input_data->input + input_data->cursor_pos + len,
                input_data->input_len - input_data->cursor_pos);
        for (uint8_t i = 0; i <= len; i++)
            input_data->input[input_data->input_len - i] = '\0';
        input_data->input_len -= len;
        printf("\x1B[P");
        int8_t c_len = utf8_char_len(
            input_data->input[input_data->cursor_pos]);
        if (c_len > 1)
            input_data->cursor_pos += c_len - 1;
        return true;
    }
    return false;
}

bool process_home_end_keys(InputBuffer *input_data)
{
    if (input_data->read[2] == 'H' || (input_data->read[2] == '1' &&
    input_data->read[3] == '~')) {
        while (input_data->cursor_pos > 0) {
            uint8_t prev_len = previous_utf8_char_length(input_data->input,
                input_data->cursor_pos);
            input_data->cursor_pos -= prev_len == 1 ? 1 : prev_len;
            printf("\x1b[D");
        }
        return true;
    }
    if (input_data->read[2] == 'F' || (input_data->read[2] == '4' &&
    input_data->read[3] == '~')) {
        while (input_data->cursor_pos < input_data->input_len) {
            input_data->cursor_pos += utf8_char_len(
                input_data->input[input_data->cursor_pos]);
            printf("\x1b[C");
        }
        return true;
    }
    return false;
}

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

bool process_enter_key(ShellContext *context, InputBuffer *input_data)
{
    // Handle enter key here
}

bool process_regular_key(ShellContext *context, InputBuffer *input_data) {
    // Handle regular key here
}

void process_key(ShellContext *context, InputBuffer *input_data)
{
    if (input_data->read[0] == '\x1b' && input_data->read[1] == '[') {
        if (process_arrow_keys(input_data)) return;
        if (process_delete_key(input_data)) return;
        if (process_home_end_keys(input_data)) return;
    }
    if (input_data->read[0] == 0x7f) {
        process_backspace_key(input_data);
        return;
    }
    if (strchr(input_data->read, '\n')) {

    } else {
    }
}

int shell(envdata_t *env, struct termios *old_term, struct termios *new_term)
{
    ShellContext context = {env, 0, false};
    InputBuffer input_data = {{0}, 0, 0, {0}, false};
    setlocale(LC_ALL, ""); // Set the locale to the user's default locale
    
    if (isatty(0)) {
        configure_terminal(new_term, old_term);
        write_prompt(env);
        input_data.is_tty = true;
    }
    while (1) {
        fflush(stdout);
        memset(input_data.read, 0, 4);
        input_data.read_len = read(STDIN_FILENO, input_data.read, 4);
        if (input_data.read[0] == 0x7f) {
            if (input_data.cursor_pos <= 0 || input_data.input_len <= 0 ||
                input_data.cursor_pos > input_data.input_len)
                continue;
            uint8_t len = previous_utf8_char_length(input_data.input, input_data.cursor_pos);
            if (len > input_data.cursor_pos || input_data.cursor_pos - len < 0)
                continue;
            if (input_data.cursor_pos >= len)
                len = previous_utf8_char_length(input_data.input, input_data.cursor_pos -
                    previous_utf8_char_length(input_data.input, input_data.cursor_pos));
            if (input_data.cursor_pos < input_data.input_len)
                memmove(input_data.input + input_data.cursor_pos - len,
                    input_data.input + input_data.cursor_pos,(input_data.input_len - input_data.cursor_pos));
            for (uint8_t i = 0; i <= len; i++)
                input_data.input[input_data.input_len - i] = '\0';
            input_data.input_len -= len;
            input_data.cursor_pos -= len;
            printf("\x1B[D\x1B[P");
            continue;
        }
        if (strchr(input_data.read, '\n')) {
            int8_t len = utf8_char_len(input_data.read[0]);
                if (len == 1 && input_data.read_len > 1)
                    len = input_data.read_len;
            memcpy(input_data.input + input_data.cursor_pos, input_data.read, len);
                input_data.input_len += len;
                input_data.cursor_pos += len;

            // Process the input buffer when the 'Enter' key is pressed
            operate_on_previous_command(input_data.input, env->history);
            if (input_data.input[0] == '!') {
                continue;
            }
            add_line_to_history(env->history, input_data.input);

            if (input_data.is_tty)
                printf("\n");
            context.status = run_user_input(input_data.input, env, &context.exiting);
            if (context.exiting || !input_data.is_tty)
                return (context.status);

            // Clear the input buffer and reset the buffer length and cursor position
            memset(input_data.input, 0, sizeof(input_data.input));
            input_data.input_len = input_data.cursor_pos = 0;
            write_prompt(env);
            continue;
        } else {
            if (input_data.input_len + input_data.read_len > sizeof(input_data.input))
                continue;
            int8_t len = utf8_char_len(input_data.read[0]);
            if (len == 1 && input_data.read_len > 1)
                len = input_data.read_len;
            if (input_data.cursor_pos >= input_data.input_len) {
                memcpy(input_data.input + input_data.cursor_pos, input_data.read, len);
                input_data.input_len += len;
                input_data.cursor_pos += len;

                // Add a null terminator
                input_data.input[input_data.input_len] = '\0';
                if (input_data.is_tty)
                    printf("%.*s", len, input_data.read);
                continue;
            }
            int8_t prev_len = utf8_char_len(
                input_data.input[input_data.cursor_pos]);
            if (prev_len <= 0)
                prev_len = previous_utf8_char_length(input_data.input,
                    input_data.cursor_pos);
            // Move the characters to the right of the cursor
            if (prev_len > 1 && len > 1) {
                memmove(input_data.input + input_data.cursor_pos + len - 1,
                        input_data.input + input_data.cursor_pos - (prev_len - 1),
                        (input_data.input_len - input_data.cursor_pos) +
                        (prev_len - 1));
                // Insert the new character
                memcpy(input_data.input + input_data.cursor_pos - (prev_len - 1), input_data.read,
                       len);
                // Clear the line to the right of the cursor
                // Print the updated buffer from the current cursor position
                printf("\x1b[K%s", input_data.input + input_data.cursor_pos - (prev_len - 1));

                // Increment the input_data.input_len and input_data.cursor_pos
                input_data.input_len += len;
                input_data.cursor_pos += len;
            } else {
                uint8_t offset = prev_len > 1 ? 0 : len;
                memmove(input_data.input + input_data.cursor_pos + offset,
                        input_data.input + input_data.cursor_pos - (prev_len - 1),
                        (input_data.input_len - input_data.cursor_pos) + (prev_len
                        - 1));
                // Insert the new character
                memcpy(input_data.input + input_data.cursor_pos - (prev_len - 1), input_data.read,
                       len);
                // Clear the line to the right of the cursor
                // Print the updated buffer from the current cursor position
                printf("\x1b[K%s", input_data.input + input_data.cursor_pos - (prev_len - 1));

                // Increment the input_data.input_len and input_data.cursor_pos
                input_data.input_len += len;
                input_data.cursor_pos += len;
            }

            // Add a null terminator
            input_data.input[input_data.input_len] = '\0';

            // Calculate the display width difference between the current cursor position
            // and the end of the buffer
            uint16_t i;
            i = input_data.input_len - 1;
            while (i >= input_data.cursor_pos) {
                int8_t c_len = utf8_char_len(input_data.input[i]);
                if (c_len <= 0)
                    c_len = previous_utf8_char_length(input_data.input, i);
                i -= c_len;
                printf("\x1b[D");
            }
        }
    }
}
