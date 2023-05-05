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

int write_prompt(envdata_t *env)
{
    if (!env->is_fallback) {
        printf("<%s@%s %s >$ ", env->user, env->hostname, env->cwd);
    } else
        printf("> ");
    fflush(stdout);
    return (1);
}

int shell(envdata_t *env)
{
    int status = 0, exiting = 0;
    char input[4096];
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
                        cursor_position++;
                        printf("\x1b[C");
                    }
                } else if (c == 'D') {
                    // Left arrow key
                    if (cursor_position > 0) {
                        cursor_position--;
                        printf("\x1b[D");
                    }
                }
                fflush(stdout);
                continue;
            }
        } else if (c == '\n') {
            // Null-terminate the input buffer
            input[buffer_length] = '\0';

            // Process the input buffer when the 'Enter' key is pressed
            operate_on_previous_command((char **) &input, env->history);
            if (input[0] == '!') {
                continue;
            }
            add_line_to_history(env->history, input);
            status = run_user_input(input, env, &exiting);
            if (exiting)
                return (status);

            // Clear the input buffer and reset the buffer length and cursor position
            memset(input, 0, sizeof(input));
            buffer_length = 0;
            cursor_position = 0;
            write_prompt(env);
        } else if (c == 'q') {
            break;
        } else if (c == 0x7f) {
            if (cursor_position > 0 && buffer_length > 0 && cursor_position < buffer_length) {
                memmove(input + cursor_position - 1, input + cursor_position,
                        (buffer_length - cursor_position) * sizeof(char));
                buffer_length--;
                cursor_position--;
                printf("\x1B[D\x1B[P");
                fflush(stdout);
            }
            if (cursor_position == buffer_length && buffer_length > 0 && cursor_position > 0) {
                buffer_length--;
                cursor_position--;
                input[cursor_position] = '\0';
                printf("\x1B[D\x1B[P");
                fflush(stdout);
            }
            fflush(stdout);
            continue;
        } else {
            // Read the rest of the UTF-8 character bytes
            int remaining_bytes = 0;
            if ((c & 0xE0) == 0xC0) {
                remaining_bytes = 1;
            } else if ((c & 0xF0) == 0xE0) {
                remaining_bytes = 2;
            } else if ((c & 0xF8) == 0xF0) {
                remaining_bytes = 3;
            }

            // Read the remaining bytes of the character and add them to the input buffer
            char utf8_char[4] = {c};
            for (int i = 0; i < remaining_bytes; i++) {
                utf8_char[i + 1] = getchar();
            }

            if (buffer_length + remaining_bytes + 1 < sizeof(input)) {
                if (cursor_position < buffer_length) {
                    // Move the characters to the right of the cursor
                    memmove(input + cursor_position + remaining_bytes + 1, input + cursor_position, buffer_length - cursor_position);

                    // Insert the new character
                    memcpy(input + cursor_position, utf8_char, remaining_bytes + 1);

                    // Clear the line to the right of the cursor
                    printf("\x1b[K");
                    fflush(stdout);

                    // Print the updated buffer from the current cursor position
                    printf("%s", input + cursor_position);
                    fflush(stdout);

                    // Increment the buffer_length and cursor_position
                    buffer_length += remaining_bytes == 0 ? 1 : remaining_bytes;
                    cursor_position++;

                    // Add a null terminator
                    input[buffer_length] = '\0';

                    // Move the cursor back to the correct position
                    printf("\x1b[%dD", (int)buffer_length - (int)cursor_position);
                    fflush(stdout);
                } else {
                    memcpy(input + cursor_position, utf8_char, remaining_bytes + 1);
                    buffer_length += remaining_bytes == 0 ? 1 : remaining_bytes;
                    cursor_position++;

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
