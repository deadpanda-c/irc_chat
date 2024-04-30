CC	=	gcc

SRC	=	$(shell find . -name "*.c")

OBJ	=	$(SRC:.c=.o)

NAME	=	../irc_server

CFLAGS	=	-W -Wall -Wextra -Werror -Iinclude -I../libs -g3

LDFLAGS	=	-L../libs/myteams -lmyteams -luuid

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) $(CFLAGS)

clean:
	find . -name "*.o" -delete

fclean:	clean
	rm -rf $(NAME)

re:	fclean	all
