NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address,leak

SRCS = 

all: $(NAME)

$(NAME):
	@$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
	@echo "Philosophers compiled successfully!"

clean:
	@rm -rf *.o
	@echo "Cleaned up object!"

fclean: clean
	@rm -rf $(NAME)
	@echo "Fully cleaned up the project!"

re: fclean all

norminette:
	norminette $(SRCS)

.PHONY: all clean fclean re norminette