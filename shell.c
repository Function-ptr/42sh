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

uint8_t write_prompt(envdata_t *env)
{
    printf(env->is_fallback ? "> " : "<%s@%s %s >$ ", env->user,
        env->hostname, env->cwd);
    fflush(stdout);
    return 1;
}

uint8_t utf8_char_length(uint8_t byte)
{
    return (byte & 0x80) == 0x00 ? 1 :
           (byte & 0xE0) == 0xC0 ? 2 :
           (byte & 0xF0) == 0xE0 ? 3 :
           (byte & 0xF8) == 0xF0 ? 4 : -1;
}

uint8_t previous_utf8_char_length(const char input[4], uint16_t cursor_position)
{
    uint8_t len = 1;

    for (uint8_t i = 0; i < 3 && (input[cursor_position] & 0xC0) == 0x80; ++i) {
        len++;
        if (cursor_position > 0) {
            cursor_position--;
        } else {
            break;
        }
    }
    return len;
}

int shell(envdata_t *env, struct termios *old_term, struct termios *new_term)
{
    uint8_t status;
    char input[4096] = {0};
    uint16_t buffer_length = 0;
    uint16_t cursor_position = 0;
    setlocale(LC_ALL, ""); // Set the locale to the user's default locale
    bool is_tty = false, exiting = false;

    // Buffer to hold input data
    char buf[4] = {0};
    if (isatty(0)) {
        configure_terminal(new_term, old_term);
        write_prompt(env);
        is_tty = true;
    }
    while (1) {
        fflush(stdout);
        memset(buf, 0, sizeof(buf));
        uint8_t read_len = read(STDIN_FILENO, buf, sizeof(buf));
        if (buf[0] == '\x1b' && buf[1] == '[') {
            // Check for arrow key escape sequence
            if (buf[2] == 'C' && cursor_position < buffer_length) {
                // Right arrow key
                cursor_position += utf8_char_length
                    (input[cursor_position + 1]);
                printf("\x1b[C");
                continue;
            } if (buf[2] == 'D' && cursor_position > 0) {
                // Left arrow key
                int prev_len = previous_utf8_char_length(input, cursor_position);
                cursor_position -= prev_len == 1 ? 1 : prev_len;
                printf("\x1b[D");
                continue;
            } if (buf[2] == '3' && buf[3] == '~' && cursor_position < buffer_length) {
                // Delete key
                int len = utf8_char_length(input[cursor_position]);
                memmove(input + cursor_position, input + cursor_position + len,
                        (buffer_length - cursor_position) * sizeof(char));
                for (int i = 0; i <= len; i++)
                    input[buffer_length - i] = '\0';
                buffer_length -= len;
                printf("\x1B[P");
                int c_len = utf8_char_length(input[cursor_position]);
                if (c_len > 1)
                    cursor_position += c_len - 1;
                continue;
            } if (buf[2] == 'H' || (buf[2] == '1' && buf[3] == '~')) {
                // Home key
                while (cursor_position > 0) {
                    int prev_len = previous_utf8_char_length(input, cursor_position);
                    cursor_position -= prev_len == 1 ? 1 : prev_len;
                    printf("\x1b[D");
                }
                continue;
            } if (buf[2] == 'F' || (buf[2] == '4' && buf[3] == '~')) {
                // End key
                while (cursor_position < buffer_length) {
                    cursor_position += utf8_char_length(input[cursor_position]);
                    printf("\x1b[C");
                }
                continue;
            }
            continue;
        }
        if (buf[0] == 0x7f) {
            if (cursor_position <= 0 || buffer_length <= 0 ||
                cursor_position > buffer_length)
                continue;
            int len = previous_utf8_char_length(input, cursor_position -
                previous_utf8_char_length(input, cursor_position));
            if (cursor_position < buffer_length)
                memmove(input + cursor_position - len,
                    input + cursor_position,(buffer_length - cursor_position));
            for (int i = 0; i <= len; i++)
                input[buffer_length - i] = '\0';
            buffer_length -= len;
            cursor_position -= len;
            printf("\x1B[D\x1B[P");
            continue;
        }
        if (strchr(buf, '\n')) {
            int len = utf8_char_length(buf[0]);
                if (len == 1 && read_len > 1)
                    len = read_len;
            memcpy(input + cursor_position, buf, len);
                buffer_length += len;
                cursor_position += len;

            // Process the input buffer when the 'Enter' key is pressed
            operate_on_previous_command(input, env->history);
            if (input[0] == '!') {
                continue;
            }
            add_line_to_history(env->history, input);

            if (is_tty)
                printf("\n");
            status = run_user_input(input, env, &exiting);
            if (exiting || !is_tty)
                return (status);

            // Clear the input buffer and reset the buffer length and cursor position
            memset(input, 0, sizeof(input));
            buffer_length = cursor_position = 0;
            write_prompt(env);
            continue;
        } else {
            if (buffer_length + read_len > sizeof(input))
                continue;
            uint8_t len = utf8_char_length(buf[0]);
            if (len == 1 && read_len > 1)
                len = read_len;
            if (cursor_position == buffer_length) {
                memcpy(input + cursor_position, buf, len);
                buffer_length += len;
                cursor_position += len;

                // Add a null terminator
                input[buffer_length] = '\0';
                if (is_tty)
                    printf("%.*s", len, buf);
                continue;
            }
            uint8_t prev_len = utf8_char_length(input[cursor_position]);
            if (prev_len <= 0)
                prev_len = previous_utf8_char_length(input,
                    cursor_position);
            // Move the characters to the right of the cursor
            if (prev_len > 1 && len > 1) {
                memmove(input + cursor_position + len - 1,
                        input + cursor_position - (prev_len - 1),
                        (buffer_length - cursor_position) +
                        (prev_len - 1));
                // Insert the new character
                memcpy(input + cursor_position - (prev_len - 1), buf,
                       len);
                // Clear the line to the right of the cursor
                // Print the updated buffer from the current cursor position
                printf("\x1b[K%s", input + cursor_position - (prev_len - 1));

                // Increment the buffer_length and cursor_position
                buffer_length += len;
                cursor_position += len;
            } else {
                uint8_t offset = prev_len > 1 ? 0 : len;
                memmove(input + cursor_position + offset,
                        input + cursor_position - (prev_len - 1),
                        (buffer_length - cursor_position) + (prev_len
                        - 1));
                // Insert the new character
                memcpy(input + cursor_position - (prev_len - 1), buf,
                       len);
                // Clear the line to the right of the cursor
                // Print the updated buffer from the current cursor position
                printf("\x1b[K%s", input + cursor_position - (prev_len - 1));

                // Increment the buffer_length and cursor_position
                buffer_length += len;
                cursor_position += len;
            }

            // Add a null terminator
            input[buffer_length] = '\0';

            // Calculate the display width difference between the current cursor position
            // and the end of the buffer
            uint16_t i;
            i = buffer_length - 1;
            while (i >= cursor_position) {
                uint8_t c_len = utf8_char_length(input[i]);
                if (c_len <= 0)
                    c_len = previous_utf8_char_length(input, i);
                i -= c_len;
                printf("\x1b[D");
            }
        }
    }
}
