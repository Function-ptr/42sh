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

int write_prompt(envdata_t *env)
{
    printf(env->is_fallback ? "> " : "<%s@%s %s >$ ", env->user,
        env->hostname, env->cwd);
    fflush(stdout);
    return 1;
}

int utf8_char_length(uint8_t byte)
{
    return (byte & 0x80) == 0x00 ? 1 :
           (byte & 0xE0) == 0xC0 ? 2 :
           (byte & 0xF0) == 0xE0 ? 3 :
           (byte & 0xF8) == 0xF0 ? 4 : -1;
}

int previous_utf8_char_length(const char *input, uint16_t cursor_position)
{
    int len = 1;

    while (cursor_position > 0 && (input[cursor_position] & 0xC0) == 0x80) {
        len++;
        cursor_position--;
    }
    return len;
}

int shell(envdata_t *env)
{
    int status = 0, exiting = 0;
    char input[4096] = {0};
    size_t buffer_length = 0;
    size_t cursor_position = 0;
    setlocale(LC_ALL, ""); // Set the locale to the user's default locale

    int c;
    if (isatty(0))
        write_prompt(env);
    while (1) {
        c = getchar();
        if (c == '\x1b') {
            // Check for arrow key escape sequence
            if (getchar() == '[') {
                c = getchar();
                if (c == 'C') {
                    // Right arrow key
                    if (cursor_position < buffer_length) {
                        cursor_position += utf8_char_length
                            (input[cursor_position + 1]);
                        printf("\x1b[C");
                    }
                } else if (c == 'D') {
                    // Left arrow key
                    if (cursor_position > 0) {
                        int prev_len = previous_utf8_char_length(input, cursor_position);
                        cursor_position -= prev_len == 1 ? 1 : prev_len;
                        printf("\x1b[D");
                    }
                } else if (c == '3') {
                    c = getchar();
                    if (c == '~') {
                        // Delete key
                        if (cursor_position < buffer_length) {
                            int len = utf8_char_length(input[cursor_position]);
                            memmove(input + cursor_position, input + cursor_position + len,
                                    (buffer_length - cursor_position) * sizeof(char));
                            for (int i = 0; i <= len; i++)
                                input[buffer_length - i] = '\0';
                            buffer_length -= len;
                            printf("\x1B[P");
                            fflush(stdout);
                            int c_len = utf8_char_length(input[cursor_position]);
                            if (c_len > 1)
                                cursor_position += c_len - 1;
                        }
                    }
                } else if (c == 'H' || c == '1') {
                    // Home key
                    if (c == '1' && getchar() != '~')
                        continue;
                    while (cursor_position > 0) {
                        int prev_len = previous_utf8_char_length(input, cursor_position);
                        cursor_position -= prev_len == 1 ? 1 : prev_len;
                        printf("\x1b[D");
                    }
                } else if (c == 'F' || c == '4') {
                    // End key
                    if (c == '4' && getchar() != '~')
                        continue;
                    while (cursor_position < buffer_length) {
                        cursor_position += utf8_char_length(input[cursor_position]);
                        printf("\x1b[C");
                    }
                }
                fflush(stdout);
                continue;
            }
        } else if (c == '\n') {
            // Null-terminate the input buffer
            input[buffer_length] = '\0';

            // Process the input buffer when the 'Enter' key is pressed
            operate_on_previous_command(input, env->history);
            if (input[0] == '!') {
                continue;
            }
            add_line_to_history(env->history, input);
            status = run_user_input(input, env, &exiting);
            if (exiting)
                return (status);

            // Clear the input buffer and reset the buffer length and cursor position
            memset(input, 0, sizeof(input));
            buffer_length = cursor_position = 0;
            write_prompt(env);
        } else if (c == 0x7f) {
            int len = previous_utf8_char_length(input, cursor_position - 1);
            if (cursor_position < buffer_length && cursor_position > 0 &&
                buffer_length > 0)
                memmove(input + cursor_position - len,
                    input + cursor_position,(buffer_length - cursor_position));
            for (int i = 0; i <= len; i++)
                input[buffer_length - i] = '\0';
            buffer_length -= len;
            cursor_position -= len;
            printf("\x1B[D\x1B[P");
            fflush(stdout);
        } else {
            // Read the rest of the UTF-8 character bytes
            int remaining_bytes = utf8_char_length(c) - 1;

            // Read the remaining bytes of the character and add them to the input buffer
            char utf8_char[4] = {(char)c};
            for (int i = 0; i < remaining_bytes; i++) {
                utf8_char[i + 1] = (char)getchar();
            }

            if (buffer_length + remaining_bytes + 1 < sizeof(input)) {
                int len = utf8_char_length(utf8_char[0]);
                if (cursor_position < buffer_length) {
                    size_t i;
                    int prev_len = utf8_char_length(input[cursor_position]);
                    if (prev_len <= 0)
                        prev_len = previous_utf8_char_length(input,
                                                             cursor_position);
                    // Move the characters to the right of the cursor
                    if (prev_len > 1 && len > 1) {
                        memmove(input + cursor_position + len - 1,
                                input + cursor_position - (prev_len - 1),
                                (buffer_length - cursor_position) +
                                (prev_len - 1) *
                                sizeof(char));
                        // Insert the new character
                        memcpy(input + cursor_position - (prev_len - 1), utf8_char, len);
                        // Clear the line to the right of the cursor
                        printf("\x1b[K");
                        fflush(stdout);

                        // Print the updated buffer from the current cursor position
                        printf("%s", input + cursor_position - (prev_len - 1));
                        fflush(stdout);
                        // Increment the buffer_length and cursor_position
                        buffer_length += len;
                        cursor_position += len;
                    } else {
                        int offset = prev_len > 1 ? 0 : len;
                        memmove(input + cursor_position + offset,
                                input + cursor_position - (prev_len - 1),
                                (buffer_length - cursor_position) + (prev_len
                                - 1) *
                                sizeof(char));
                        // Insert the new character
                        memcpy(input + cursor_position - (prev_len - 1), utf8_char, len);
                        // Clear the line to the right of the cursor
                        printf("\x1b[K");
                        fflush(stdout);

                        // Print the updated buffer from the current cursor position
                        printf("%s", input + cursor_position - (prev_len - 1));
                        fflush(stdout);
                        // Increment the buffer_length and cursor_position
                        buffer_length += len;
                        cursor_position += len;
                    }

                    // Add a null terminator
                    input[buffer_length] = '\0';

                    // Calculate the display width difference between the current cursor position
                    // and the end of the buffer
                    i = buffer_length - 1;
                    while (i >= cursor_position) {
                        int c_len = utf8_char_length(input[i]);
                        if (c_len <= 0)
                            c_len = previous_utf8_char_length(input, i);
                        i -= c_len;
                        printf("\x1b[D");
                    }

                    fflush(stdout);
                } else {
                    memcpy(input + cursor_position, utf8_char, len);
                    buffer_length += len;
                    cursor_position += len;

                    // Add a null terminator
                    input[buffer_length] = '\0';

                    printf("\x1b[K%s", utf8_char);
                }
                fflush(stdout);
            }
        }
    }
    return (status);
}
