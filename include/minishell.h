/*
** EPITECH PROJECT, 2023
** minishell.h
** File description:
** minishell1
*/

#ifndef MINISHELL1_MINISHELL_H
    #define MINISHELL1_MINISHELL_H
        #include <unistd.h>
        #include <stdio.h>
        #include <stdlib.h>
        #include <fcntl.h>
        #include <time.h>
        #include <string.h>
        #include <signal.h>
        #include <stddef.h>
        #include <sys/stat.h>
        #include <sys/types.h>
        #include <dirent.h>
        #include <sys/wait.h>
        #include "my.h"
        #include "printf.h"
        #include <errno.h>
        #include <stdbool.h>

    typedef struct envvar {
        char *var;
        struct envvar *next;
    } envvar_t;

    typedef struct path_dir {
        char *dir;
        struct path_dir *next;
    } pathdir_t;

    typedef struct env_data {
        char is_fallback;
        envvar_t **env;
        char *path;
        pathdir_t **path_dirs;
        char *cwd;
        char *prevcwd;
        char *user;
        size_t userlen;
        char *hostname;
        size_t hostlen;
    } envdata_t;

    typedef struct command {
        bool pipe_in;       // is input piped (incompatible with redirect_in)
        bool pipe_out;      // is output piped (incompatible with redirect_out)
        bool redirect_in;   // is input redirected ( < )
        bool redirect_in_word_wait; // is input redirected with a word_wait (<<)
        char *awaited_word; // The word marking the end of input with <<
        bool redirect_out;  // is output redirected ( > )
        bool redirect_out_append; // is output redirected with append ( >> )
        char *command;      // command string
        char next_separator; // next separator ->  "| ; \0"
        int in_fd;          // input file descriptor (default 0)
        int out_fd;         // output file descriptor (default 1)
        int pipe_in_fd;     // file descriptor for input pipe
    } command_t;




///////////////
/// General ///
///////////////

int shell(envdata_t *env);
int is_argv_long_enough(char *command, int cap, char *func);
char *get_binary_name(char *str);
int is_path(char *str);
int array_len(char **arr);

////////////////
/// Builtins ///
////////////////

int builtin_funcs(command_t *cmd, envdata_t *env);
void show_environment(envvar_t **env, command_t *command);
int change_dir(envdata_t *env, char *input);
void unset_env(envvar_t **env, char *inp);
void set_env(envvar_t **env, command_t *command);
int exit_with_status(command_t *command);
bool is_a_builtin(char *binary);

////////////////////////
/// Execute binaries ///
////////////////////////

int run_specified_path(command_t *cmd, envvar_t **env);
int check_exit_status(int status);
int run_binary_file(char *filepath, command_t *command, envvar_t **env);
int execute_from_path(command_t *command, pathdir_t **path_dirs,
    envvar_t **env);
int detect_command_type_and_run(command_t *command, int *exiting,
    envdata_t *env);
int run_user_input(char *input, envdata_t *env, int *exiting);

///////////////////
/// Environment ///
///////////////////

int compare_variable_name(char *var, char *name);
char **get_environment(envvar_t **env);
void set_value(envvar_t *var, char *varname, char *value);
char *get_environment_variable(envvar_t **env, char *var);
void set_environment_variable(envvar_t **env, char *var, char *newvar);
char *get_variable_name(char *args);
void reverse_environment_variables(envvar_t **begin);
void clear_environment_variables(envvar_t **list);
void add_environment_variable(envvar_t **env, char *var);
void clear_environment(envdata_t *envdata);
void duplicate_environment(char **env, envvar_t **list);
void reverse_path_directories(pathdir_t **begin);
pathdir_t **get_path_directories(char *path);
char *get_path_variable(envvar_t **env);
envdata_t *initialize_envdata(char **env);
envdata_t *initialize_fallback_environment(void);

//////////////
/// Errors ///
//////////////

void name_not_alphanumeric(void);
bool name_does_not_start_with_letter(char c);
void ambigous_redirection(bool input);
void missing_name_for_redirection(void);
void null_command(void);
void exit_with_error(envdata_t *env);
void execution_error(char *command);

////////////
/// PATH ///
////////////

void clear_path_directories(pathdir_t **list);
void add_path_directory(pathdir_t **pathdirs, char *dir, int len);

///////////////
/// Parsing ///
///////////////

command_t **cut_input_to_commands(char *input);
command_t *parse_single_command(char *comm, command_t *prev, char next_sep,
    int **data);
void detect_redirections(command_t *command, char *comm, char next_sep,
    int *status);
int get_redirections_file_descriptors(command_t *command, char *comm);
char *remove_spaces_in_command(char *comm, char sep, bool pipe_in, int *status);
bool parse_and_load_redirections(command_t *command);
void get_word_wait_input(command_t *cmd);
int load_redirections_for_command(command_t *command);
void free_commands(command_t **commands);
void free_command(command_t *command);

#endif //MINISHELL1_MINISHELL_H
