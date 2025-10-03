NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

# Directories
SRC_DIR = src/
INC_DIR = inc/
OBJ_DIR = obj/
GNL_DIR = $(SRC_DIR)get_next_line/
PRINTF_DIR = $(SRC_DIR)ft_printf/

# Source files
SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
	ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
	ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
	ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_atol.c \
	free_array.c free_and_null.c copy_array.c is_whitespace.c	ft_strndup.c

# Get Next Line files
GNL_SRCS = get_next_line.c get_next_line_utils.c

# Printf files
PRINTF_SRCS = ft_printf.c print_char.c print_str.c print_ptr.c print_int.c \
	print_uint.c print_hex.c

# Full paths for all source files
SRC_PATHS = $(addprefix $(SRC_DIR), $(SRCS))
GNL_PATHS = $(addprefix $(GNL_DIR), $(GNL_SRCS))
PRINTF_PATHS = $(addprefix $(PRINTF_DIR), $(PRINTF_SRCS))

# All source files combined
ALL_SRCS = $(SRC_PATHS) $(GNL_PATHS) $(PRINTF_PATHS)

# Objects will be in the obj directory
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o)) $(addprefix $(OBJ_DIR), $(notdir $(GNL_PATHS:.c=.o))) $(addprefix $(OBJ_DIR), $(notdir $(PRINTF_PATHS:.c=.o)))

# Rules
all: $(NAME)

# Create obj directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Compile libft source files
$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Compile GNL source files
$(OBJ_DIR)%.o: $(GNL_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Compile Printf source files
$(OBJ_DIR)%.o: $(PRINTF_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

# Phony
.PHONY: all clean fclean re