SRCS = srcs/main.c srcs/parsing.c srcs/init_philo.c srcs/free.c srcs/utils.c srcs/philo.c srcs/monitoring.c srcs/init_data.c

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