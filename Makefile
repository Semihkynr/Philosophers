NAME=philo

SRCS= main.c utils.c
CFLAGS=-Wall -Wextra -Werror -pthread


$(NAME): $(SRCS) 
	cc  -o  $(NAME)  $(CFLAGS) $(SRCS)

all: $(NAME)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re