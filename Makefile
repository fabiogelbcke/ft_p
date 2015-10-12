CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC_C =	mainclient.c \
	client_local_functions.c \
	client_functions.c \

SRC_S = mainserver.c \
	server_functions.c \
	utils.c \

OBJ_C = $(SRC_C:.c=.o)

OBJ_S = $(SRC_S:.c=.o)

LIB = libft/libft.a

NAME_C = testfoler/client

NAME_S = serveur

all:	$(NAME_C) $(NAME_S)

$(NAME_C): $(OBJ_C)
	make -C ./libft
	$(CC) -o $(NAME_C) $(FLAGS) $(OBJ_C) $(LIB)

$(NAME_S): $(OBJ_S)
	make -C ./libft
	$(CC) -o $(NAME_S) $(FLAGS) $(OBJ_S) $(LIB)

clean:
	rm -f $(OBJ_C) $(OBJ_S)

fclean:	clean
	rm -rf $(NAME_C) $(NAME_S)

re: fclean all

.PHONY: all clean fclean re
