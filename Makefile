NAME = fdf

SRC_DIR = ./

INCLUDE = -I /usr/local/include/minilibx/ -I ./includes/

LIB_DIR = /usr/local/lib/minilibx

SRCS = test.c
SRC_FILES = $(addprefix $(SRC_DIR), $(SRCS))

OBJ_FILES = $(SRC_FILES:.c=.o)

CC = gcc

CFLAGS = -Wextra #-Werror -Wall

all : $(NAME)

bonus : $(NAME_BONUS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -Imlx_linux -O3 -c $< -o $@

$(NAME) : $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -Lmlx_linux -lmlx_Linux -L$(LIB_DIR) -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean :
	rm -f *.o */*.o

fclean : clean
	rm -f $(NAME) $(NAME_BONUS)

re : fclean all

.PHONY : clean fclean all re