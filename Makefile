NAME = philo

SRC = main.c helpers.c init_and_finish.c threads.c judge.c

OBJ = main.o helpers.o init_and_finish.o threads.o judge.o

CFLAGS = -Wall -Wextra -Werror -O3 -pthread

all: $(NAME)

$(NAME): $(OBJ)
	@cc $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	@rm -f $(OBJ)

go: all clean

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
