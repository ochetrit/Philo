SRCS = main.c  parsing.c init_philo.c free.c utils.c philo.c monitoring.c init_data.c

OBJS = $(SRCS:.c=.o)

NAME = philo

CC = cc

RM = rm -f

FLAGS = -Wall -Wextra -Werror -g3

$(NAME):  $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) -c $(FLAGS) $< -o $@

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re