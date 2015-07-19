CC = gcc

FLAGS = -g -Wall -Wextra -Werror

SRC_C =	mainclient.c \

SRC_S = mainserver.c \

OBJ_C	= $(SRC_C:.c=.o)

OBJ_S	= $(SRC_S:.c=.o)

LIB 	= libft/libft.a

NAME_C = client

NAME_S = server

client: $(NAME_C)

server: $(NAME_S)

$(NAME_C): $(OBJ_C)
	$(MAKE) -C ./libft	
	$(CC) -o $(NAME_C) $(FLAGS) $(OBJ_C) $(LIB)

$(NAME_S): $(OBJ_S)
	$(MAKE) -C ./libft
	$(CC) -o $(NAME_S) $(FLAGS) $(OBJ_S) $(LIB)

all: client server

clean:
	rm -f $(OBJ_C) $(OBJ_S)

fclean:	clean
	rm -f $(NAME_S) $(NAME_C)

re: fclean all

.PHONY: all clean fclean re
