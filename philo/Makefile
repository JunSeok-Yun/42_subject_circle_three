NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf
FILES = error.c free.c main.c utils.c utils2.c utils3.c utils4.c

OBJS = $(FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
				@${CC}	${CFLAGS}	${OBJS}	-o	${NAME}

clean:
				$(RM)	$(OBJS)

fclean:	clean
				$(RM)	$(NAME)

re:				fclean	all

.PHONY: all	clean	fclean	re