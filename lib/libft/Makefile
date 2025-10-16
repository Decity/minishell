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
	ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_isthing1.c \
	ft_isthing2.c \
	ft_itoa.c \
	ft_listadd.c \
	ft_listdel.c \
	ft_listfunc.c \
	ft_listlast.c \
	ft_listnew.c \
	ft_listsize.c \
	ft_mem.c \
	ft_printf.c \
	ft_putnum.c \
	ft_putstr.c \
	ft_puttype_fd.c \
	ft_split.c \
	ft_strdup.c \
	ft_strfind.c \
	ft_strfunc.c \
	ft_strjoin.c \
	ft_strlc.c \
	ft_strlen.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tocase.c \
	get_next_line.c \
	custom/copy_array.c \
	custom/ed_convert_list.c \
	custom/free_and_null.c \
	custom/free_array.c \
	custom/ft_intlen.c \
	custom/ft_count_occurrence.c \
	custom/ft_repoint.c \
	custom/ft_strreplace.c \

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