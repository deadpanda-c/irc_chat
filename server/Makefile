CC	=	gcc

SRC	=	$(shell find . -name "*.c")

OBJ	=	$(SRC:.c=.o)

NAME	=	../myteams_server

CFLAGS	=	-W -Wall -Wextra -Werror -Iinclude -I../libs -g3

LDFLAGS	=	-L../libs/myteams -lmyteams

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	find . -name "*.o" -delete

fclean:	clean
	rm -rf $(NAME)

re:	fclean	all
