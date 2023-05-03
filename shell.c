/*
** EPITECH PROJECT, 2023
** shell.c
** File description:
** shell for minishell1
*/

#include "shell.h"
#include "history.h"
#include "line_edition.h"

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
            // if backspace and cursor_position > 0
            if (cursor_position > 0) {
                // remove char from buffer using memmove
                memmove(input + cursor_position - 1, input + cursor_position,
                        (buffer_length - cursor_position) * sizeof(char));
                buffer_length--;
                //input[buffer_length] = '\0';

                // go one char left
                printf("\x1b[D");
                fflush(stdout);
                cursor_position--;
                // clear the line to the right of the cursor
                //printf("%s", input + cursor_position);
                // print the updated buffer from the current cursor position
//                // move the cursor back to the correct position
                printf("\x1b[%zuD", buffer_length - cursor_position);
            }
            fflush(stdout);
            continue;
        } else {
            // Add the character to the input buffer
            if (buffer_length < sizeof(input) - 1) {
                buffer_length++;
                input[cursor_position] = (char)c;
                cursor_position++;
            }
            printf("\x1b[K%s", input + cursor_position - 1);
            fflush(stdout);
        }
    }
    return (status);
}
