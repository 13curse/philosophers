NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

SRCS = init_philo.c init.c main.c parsing.c monitoring.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Philosophers compiled successfully!"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@echo "Cleaned up object files!"

fclean: clean
	@rm -f $(NAME)
	@echo "Fully cleaned up the project!"

re: fclean all

norminette:
	norminette $(SRCS)

.PHONY: all clean fclean re norminette