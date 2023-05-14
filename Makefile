##
## EPITECH PROJECT, 2023
## Makefile 42sh
## File description:
## Makefile
##

SOURCES = . built-in execute parse errors environment history line_edition

SRCS = 	main.c	\
	shell.c	\
	sighandler.c	\
	built-in/cd.c	\
	built-in/chose_builtin.c	\
	built-in/command_is_a_builtin.c	\
	built-in/echo.c	\
	built-in/exit.c	\
	built-in/set_unset_var.c	\
	built-in/setenv.c	\
	built-in/show_environment.c	\
	built-in/unsetenv.c	\
	execute/check_program_exit_status.c	\
	execute/detect_command_type.c	\
	execute/execute_binary_file.c	\
	execute/execute_parentheses.c	\
	execute/execute_pipes_rotation.c	\
	execute/execute_using_path.c	\
	execute/run_user_input.c	\
	parse/check_argv_length.c	\
	parse/clean_commands.c	\
	parse/cut_input_to_commands.c	\
	parse/get_binary_name.c	\
	parse/handle_redirections.c	\
	parse/inhibitors.c	\
	parse/line_with_parentheses.c	\
	parse/load_redirections_for_command.c	\
	parse/my_strchr_escape.c	\
	parse/parse_single_command.c	\
	parse/quotes.c	\
	parse/remove_spaces_in_command.c	\
	parse/replace_variables.c	\
	parse/separate_args.c	\
	parse/smart_strtok.c	\
	errors/execution_errors.c	\
	errors/parsing_error.c	\
	errors/redirection_errors.c	\
	errors/setenv_errors.c	\
	environment/environment.c	\
	environment/environment_variables.c	\
	environment/getter.c	\
	environment/initialize_environment.c	\
	environment/initialize_fallback_environment.c	\
	environment/linked_lists_management.c	\
	environment/path.c	\
	environment/variables.c	\
	environment/variables_management.c	\
	history/get_file_nb_lines.c	\
	history/get_from_history.c	\
	history/history.c	\
	history/previous_args_operations.c	\
	history/previous_commands_operations.c	\
	history/show_history.c	\
	line_edition/configure_terminal.c	\
	line_edition/line_edition_utils.c	\
	line_edition/process_arrow_keys.c	\
	line_edition/process_backspace_key.c	\
	line_edition/process_ctrl_d.c	\
	line_edition/process_delete_key.c	\
	line_edition/process_enter_key.c	\
	line_edition/process_home_end_keys.c	\
	line_edition/process_key_arrow_up_down.c	\
	line_edition/process_regular_key.c	\

OBJS = 	obj/main.o	\
	obj/shell.o	\
	obj/sighandler.o	\
	obj/built-in-cd.o	\
	obj/built-in-chose_builtin.o	\
	obj/built-in-command_is_a_builtin.o	\
	obj/built-in-echo.o	\
	obj/built-in-exit.o	\
	obj/built-in-set_unset_var.o	\
	obj/built-in-setenv.o	\
	obj/built-in-show_environment.o	\
	obj/built-in-unsetenv.o	\
	obj/execute-check_program_exit_status.o	\
	obj/execute-detect_command_type.o	\
	obj/execute-execute_binary_file.o	\
	obj/execute-execute_parentheses.o	\
	obj/execute-execute_pipes_rotation.o	\
	obj/execute-execute_using_path.o	\
	obj/execute-run_user_input.o	\
	obj/parse-check_argv_length.o	\
	obj/parse-clean_commands.o	\
	obj/parse-cut_input_to_commands.o	\
	obj/parse-get_binary_name.o	\
	obj/parse-handle_redirections.o	\
	obj/parse-inhibitors.o	\
	obj/parse-line_with_parentheses.o	\
	obj/parse-load_redirections_for_command.o	\
	obj/parse-my_strchr_escape.o	\
	obj/parse-parse_single_command.o	\
	obj/parse-quotes.o	\
	obj/parse-remove_spaces_in_command.o	\
	obj/parse-replace_variables.o	\
	obj/parse-separate_args.o	\
	obj/parse-smart_strtok.o	\
	obj/errors-execution_errors.o	\
	obj/errors-parsing_error.o	\
	obj/errors-redirection_errors.o	\
	obj/errors-setenv_errors.o	\
	obj/environment-environment.o	\
	obj/environment-environment_variables.o	\
	obj/environment-getter.o	\
	obj/environment-initialize_environment.o	\
	obj/environment-initialize_fallback_environment.o	\
	obj/environment-linked_lists_management.o	\
	obj/environment-path.o	\
	obj/environment-variables.o	\
	obj/environment-variables_management.o	\
	obj/history-get_file_nb_lines.o	\
	obj/history-get_from_history.o	\
	obj/history-history.o	\
	obj/history-previous_args_operations.o	\
	obj/history-previous_commands_operations.o	\
	obj/history-show_history.o	\
	obj/line_edition-configure_terminal.o	\
	obj/line_edition-line_edition_utils.o	\
	obj/line_edition-process_arrow_keys.o	\
	obj/line_edition-process_backspace_key.o	\
	obj/line_edition-process_ctrl_d.o	\
	obj/line_edition-process_delete_key.o	\
	obj/line_edition-process_enter_key.o	\
	obj/line_edition-process_home_end_keys.o	\
	obj/line_edition-process_key_arrow_up_down.o	\
	obj/line_edition-process_regular_key.o	\

OBJ_DIR = obj

OBJ = $(SRCS:%.c=obj/%.o)

OPTI = -O3 -Ofast \
-ftree-vectorize \
-ftree-loop-distribution -funroll-all-loops -funswitch-loops \
-march=native -mtune=native -fopenmp -mavx2 \
-lm -ffast-math -mfpmath=sse \
-flto

# 	Optimization flags:

# -O3: Enables all optimizations that do not involve a space-speed tradeoff.
# -Ofast: Enables all optimizations allowed by the language standard,
# 	including potentially unsafe ones.

# 	Vectorization flags:

# -fopt-info-vec -all-ftree-vectorize: Provides information about vectorization
# 	and tree vectorization.

# 	Loop unrolling flags:

# -ftree-loop-distribution: Distributes loop iterations over multiple threads.
# -funroll-loops: Unrolls loops to reduce loop overhead.
# -funroll-all-loops: Unrolls all loops, regardless of their size.
# -funswitch-loops: Enables loop inversion for better instruction scheduling.

# 	CPU-specific flags:

# -march=native: Generates code optimized for the host machine architecture.
# -mtune=native: Generates code optimized for the host machine CPU.
# -fopenmp: Enables OpenMP parallelization.
# -mavx2: Enables use of Advanced Vector Extensions 2.

# 	Linker flags:

# -lm: Links the math library.
# -ffast-math: Enables fast math operations, which may not be IEEE compliant.
# -mfpmath=sse: Uses SSE instructions for floating-point math.

# 	Link-time optimization flags:

# -flto: Enables link-time optimization, which allows the compiler to optimize
# 	across object files.

NAME  = 42sh

CC  = gcc

LIB = -L.	-lall	\

HEADER = 	-I./include/	\
	-I./parse/include	\
	-I./history/include	\
	-I./execute/include	\
	-I./built-in/include	\
	-I./errors/include	\
	-I./environment/include	\
	-I./line_edition/include	\

CFLAGS += -Wall -Wextra  -fsanitize=undefined,address \
	$(LIB) $(HEADER)

DEBUGFLAGS += -Wall -Wextra \
	$(LIB) $(HEADER) -ggdb

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o \
$(addprefix $(OBJ_DIR)/, $(basename $(subst /,-,$<)).o)

$(NAME): $(OBJ)
	@make -s -C ./lib/all
	@$(CC) -o $(NAME) $(OBJS) $(CFLAGS)
	@echo -e "[1;32mProject built successfully[0m"

debug:	clean
	@$(CC) $(SRCS) -o $(NAME) $(DEBUGFLAGS)
	@echo -e "[1;33mProject built in debug mode[0m"

clean:
	@rm $(OBJS) .idea/ -rf
	@rm *.gcno -rf
	@find . -type f,d \( -name "*~" -o -name "\#*\#" \) -delete
	@find . -type f,d -name "vgcore*" -delete
	@echo -e "[1;34mRepo cleaned[0m"

fclean: clean
	@rm $(NAME) -rf
	@find . -type f,d -name "*.a" -delete
	@echo -e "[1;31mProject binary deleted[0m"

re: fclean $(NAME)

.PHONY: all $(NAME) clean fclean re
