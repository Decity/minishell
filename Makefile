# Executable name
NAME		= minishell

# Compiler and flags
CC			= cc
# CFLAGS		= -Wall -Werror -Wextra -g -fsanitize=address
CFLAGS = -Wall -Wextra -g3 #-Werror
MAKEFLAGS += --no-print-directory

# Directories
SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= inc
LIBFT_DIR	= lib/libft

# Source files
SRCS		= $(shell find $(SRC_DIR) -name "*.c")

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

# debug rule to add a define flag which will set debug mode to true
debug: CFLAGS += -D DEBUG=true
debug: $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)
	@echo "\e[93mCompiled in debug mode\e[0m"

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

red: fclean debug

rerun: fclean all
	./minishell

rerund: fclean debug
	./minishell

.PHONY: all clean fclean re