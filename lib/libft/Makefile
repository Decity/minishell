NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

# Directories
SRC_DIR = src/
INC_DIR = inc/
OBJ_DIR = obj/

# Source files
SRCS = \
	copy_array.c \
	free_and_null.c \
	free_array.c \
	ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_tocase.c \
	ft_intlen.c \
	ft_isthing1.c \
	ft_isthing2.c \
	ft_itoa.c \
	ft_lstadd.c \
	ft_lstdel.c \
	ft_lstfunc.c \
	ft_lstlast.c \
	ft_lstnew.c \
	ft_lstsize.c \
	ft_mem.c \
	ft_printf.c \
	ft_putnum.c \
	ft_putstr.c \
	ft_puttype_fd.c \
	ft_split.c \
	ft_strdup.c \
	ft_strfnd.c \
	ft_strfunc.c \
	ft_strjoin.c \
	ft_strlc.c \
	ft_strlen.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strtrim.c \
	ft_substr.c \
	get_next_line.c

# Full paths for all source files
SRC_PATHS = $(addprefix $(SRC_DIR), $(SRCS))

# All source files combined
ALL_SRCS = $(SRC_PATHS) $(GNL_PATHS) $(PRINTF_PATHS)

# Objects will be in the obj directory
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o)) $(addprefix $(OBJ_DIR), $(notdir $(GNL_PATHS:.c=.o))) $(addprefix $(OBJ_DIR), $(notdir $(PRINTF_PATHS:.c=.o)))

# Rules
all: $(NAME)

# Compile libft source files
$(OBJ_DIR)%.o: $(SRC_DIR)%.c Makefile
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@echo "\e[93mFinished Compiling libft\e[0m"

clean:
	@$(RM) $(OBJS)
	@$(RM) -r $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

# Phony
.PHONY: all clean fclean re