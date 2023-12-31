NAME = fdf

SRC_DIR = ./srcs/

INCLUDE = -I ./minilibx-linux/ -I ./includes/

DIR_MLX = ./minilibx-linux/

LIBFT = ./libft/libft.a

LIBMLX = ./minilibx-linux/libmlx_Linux.a

DIR_LIBFT = ./libft/

SRC_LIBFT = ft_atoi.c ft_isprint.c ft_lstlast.c ft_memmove.c ft_split.c ft_strlen.c ft_tolower.c\
ft_bzero.c ft_itoa.c ft_lstmap.c ft_memset.c ft_strchr.c ft_strmapi.c ft_toupper.c\
ft_calloc.c ft_lstadd_back.c ft_lstnew.c ft_printf.c ft_strdup.c ft_strncmp.c get_next_line.c\
ft_isalnum.c ft_lstadd_front.c ft_lstsize.c ft_putchar_fd.c ft_striteri.c ft_strnstr.c get_next_line_utils.c\
ft_isalpha.c ft_lstclear.c ft_memchr.c ft_putendl_fd.c ft_strjoin.c ft_strrchr.c\
ft_isascii.c ft_lstdelone.c ft_memcmp.c ft_putnbr_fd.c ft_strlcat.c ft_strtrim.c print_formats.c\
ft_isdigit.c ft_lstiter.c ft_memcpy.c ft_putstr_fd.c ft_strlcpy.c ft_substr.c ft_atoi_base.c

SRC_FILES_LIBFT = $(addprefix $(DIR_LIBFT), $(SRC_LIBFT))

OBJ_FILES_LIBFT = $(SRC_FILES_LIBFT:.c=.o)

SRCS = bresenham.c draw.c end_process.c key_hook.c linear_interpolation.c\
main.c matrix_1.c matrix_2.c parse_file_1.c parse_file_2.c render.c

SRC_FILES = $(addprefix $(SRC_DIR), $(SRCS))

OBJ_FILES = $(SRC_FILES:.c=.o)

CC = cc

CFLAGS = -g -Wextra -Werror -Wall

all : $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -Imlx_linux -c $< -o $@

$(LIBFT) : ${OBJ_FILES_LIBFT}
	ar -rcs ${LIBFT} ${OBJ_FILES_LIBFT}

$(LIBMLX) :
	@$(MAKE) -C $(DIR_MLX)

$(NAME) : $(OBJ_FILES) $(LIBFT) $(LIBMLX)
	$(CC) -o $(NAME) $(OBJ_FILES) -L$(DIR_MLX) -lmlx_Linux $(INCLUDE) -Imlx_linux -lXext -lX11 -lm -lz -L$(DIR_LIBFT) -lft

clean :
	rm -f *.o */*.o 

fclean : clean
	rm -f $(NAME) $(LIBFT) $(LIBMLX) $(DIR_MLX)obj/*.o

re : fclean all

.PHONY : clean fclean all re
