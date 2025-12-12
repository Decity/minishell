# Executable name
NAME		= minishell

# Compiler and flags
CC			= cc
# CFLAGS		= -Wall -Werror -Wextra -g -fsanitize=address
CFLAGS 		= -Wall -Wextra -Werror -g
MAKEFLAGS 	+= --no-print-directory

# Directories
SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= inc
LIBFT_DIR	= libft

# Source files
SRCS		= src/main.c \
			  src/init.c \
			  src/redirection.c \
			  src/signals.c \
			  src/cleanup.c \
			  src/builtins/cd.c \
			  src/builtins/echo.c \
			  src/builtins/env.c \
			  src/builtins/exit.c \
			  src/builtins/export_utils.c \
			  src/builtins/export_print.c \
			  src/builtins/export.c \
			  src/builtins/pwd.c \
			  src/builtins/unset.c \
			  src/execution/execution_binary.c \
			  src/execution/execution_builtins.c \
			  src/execution/execution_child.c \
			  src/execution/execution_pipeline_utils.c \
			  src/execution/execution_pipeline.c \
			  src/execution/execution_utils.c \
			  src/execution/execution.c \
			  src/expansion/expansion_copy.c \
			  src/expansion/expansion_remove_quotes.c \
			  src/expansion/expansion_utils.c \
			  src/expansion/expansion.c \
			  src/heredoc/heredoc_expansion_utils.c \
			  src/heredoc/heredoc_expansion.c \
			  src/heredoc/heredoc_name_generator.c \
			  src/heredoc/heredoc_utils.c \
			  src/heredoc/heredoc.c \
			  src/parsing/parsing_linked_list.c \
			  src/parsing/parsing_redirection_in.c \
			  src/parsing/parsing_redirection_out.c \
			  src/parsing/parsing_redirection.c \
			  src/parsing/parsing.c \
			  src/tokenization/tokenization_normalization_strlen_utils.c \
			  src/tokenization/tokenization_normalization_strlen.c \
			  src/tokenization/tokenization_normalization_utils.c \
			  src/tokenization/tokenization_normalization.c \
			  src/tokenization/tokenization_utils.c \
			  src/tokenization/tokenization_validation_utils.c \
			  src/tokenization/tokenization_validation.c \
			  src/tokenization/tokenization.c

# Object files
OBJS		= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Libft
LIBFT		= $(LIBFT_DIR)/libft.a

# Rules
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)
	@echo "\e[93mFinished Compiling Minishell\e[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo "\e[93mCleaned\e[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\e[93mThoroughly cleaned\e[0m"

ffclean: fclean
	@make -C $(LIBFT_DIR) fclean
	@echo "\e[93mVERY thoroughly cleaned\e[0m"

re: fclean all

rerun: fclean all
	./minishell

.PHONY: all clean fclean re