/*
** EPITECH PROJECT, 2023
** shell.c
** File description:
** shell for 42sh
*/

#include "shell.h"
#include "history.h"
#include "prompt.h"
#include "line_edition.h"

void process_key(ShellContext *context, InputBuffer *input_data)
{
    realloc_input(input_data);
    if (input_data->read[0] == '\x1b' && input_data->read[1] == '[') {
        if (process_arrow_keys(input_data, context)) return;
        if (process_delete_key(input_data)) return;
        if (process_home_end_keys(input_data)) return;
        return;
    } if (input_data->read[0] == 0x7f) {
        process_backspace_key(input_data);
        return;
    } if (input_data->read[0] == 4) {
        handle_ctrl_d(context);
        return;
    } if (input_data->read[0] == '\t') {
        process_tab_key(input_data, context);
        return;
    } if (strchr(input_data->read, '\n'))
        process_enter_key(context, input_data);
    else
        process_regular_key(input_data);
}

void write_prompt(envdata_t *env)
{
    char *user = get_environment_variable(env->env, "USER");
    char *host = get_environment_variable(env->env, "HOSTNAME");
    if (env->is_fallback) {
        printf("\033[0m\033[93;1;5m> \033[0m");
        fflush(stdout);
        return;
    }
    char *stat_icon = WIFSIGNALED(env->status) && env->status != 1 ? "⚡" :
        (env->status ? "×" : "λ");
    if (user && host)
        printf(env->starship_prompt ? STDPROMPT : NNSTDPROMPT, user + 5,
            host + 9, env->cwd, stat_icon);
    if (user && !host)
        printf(env->starship_prompt ? ONEVALPROMPT : NNOVPROMPT,
            user + 5, env->cwd, stat_icon);
    if (!user && host)
        printf(env->starship_prompt ? ONEVALPROMPT : NNOVPROMPT, host + 9,
            env->cwd, stat_icon);
    fflush(stdout);
}

char *read_stdin(void)
{
    size_t size = 1024, read;
    char *buffer = malloc(size);
    if (!buffer) return buffer;
    size_t total = 0;
    while ((read = fread(buffer + total, 1, size - total, stdin)) > 0) {
        total += read;
        if (total == size) {
            size *= 2;
            buffer = realloc(buffer, size);
        }
    }
    buffer[total] = '\0';
    return buffer;
}

static void run_non_tty(ShellContext *context)
{
    char* input = read_stdin();
    char* end_line;
    char* start_line = input;
    while ((end_line = strchr(start_line, '\n')) != NULL) {
        size_t len = end_line - start_line + 1;
        char* commands = malloc(len + 1);
        strncpy(commands, start_line, len);
        commands[len] = '\0';
        context->status = run_user_input(commands, context->env,
            &context->exiting);
        free(commands);
        start_line = end_line + 1;
    }
    context->exiting = true;
    free(input);
}

int shell(envdata_t *env, struct termios *old_term, struct termios *new_term)
{
    ShellContext context = {env, 0, false};
    InputBuffer input_data = {malloc(1024), NULL,0, 0, {0}, 0, 1,false};
    memset(input_data.input, 0, 1024);
    if (isatty(0)) {
        configure_terminal(new_term, old_term);
        write_prompt(env);
        input_data.is_tty = true;
    } else {
        run_non_tty(&context);
        free(input_data.input);
        return context.status;
    }
    while (!context.exiting) {
        input_data.read_len = read(STDIN_FILENO, input_data.read, 4);
        process_key(&context, &input_data);
        fflush(stdout);
        memset(input_data.read, 0, 5);
    }
    free(input_data.input);
    return context.status;
}
