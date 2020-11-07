NAME	= PikminC

CC	= gcc

RM	= rm -f

SRCS	= ./ressources/code/*.c \
	  ./main.c

CFLAGS = -I ./lib/my/
CFLAGS += -Wall -Wextra

all:
	 $(CC) $(SRCS) -o $(NAME) -lc_graph_prog -g3

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(NAME)

re: fclean all
