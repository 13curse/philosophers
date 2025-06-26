NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=thread

SRCS = init_philo.c init.c main.c parsing.c monitoring.c philo_actions.c philo_routine.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "                             o            o     o                                                  o                                         "
	@echo "                            <|>         _<|>_  <|>                                                <|>                                        "
	@echo "                             />                / \\                                                / >                                        "
	@echo "                 \\o_ __o    \\o__ __o      o    \\o/    o__ __o       __o__   o__ __o    \\o_ __o    \\o__ __o      o__  __o   \\o__ __o    __o__ "
	@echo "                  |    v\\    |     v\\    <|>    |    /v     v\\     />  \\   /v     v\\    |    v\\    |     v\\    /v      |>   |     |>  />  \\  "
	@echo "                 / \\    <\\  / \\     <\\   / \\   / \\  />       <\\    \\o     />       <\\  / \\    <\\  / \\     <\\  />      //   / \\   < >  \\o     "
	@echo "                 \\o/     /  \\o/     o/   \\o/   \\o/  \\         /     v\\    \\         /  \\o/     /  \\o/     o/  \\o    o/     \\o/         v\\    "
	@echo "                  |     o    |     <|     |     |    o       o       <\\    o       o    |     o    |     <|    v\\  /v __o   |           <\\   "
	@echo "                 / \\ __/>   / \\    / \\   / \\   / \\   <\\__ __/>  _\\o__</    <\\__ __/>   / \\ __/>   / \\    / \\    <\\/ > __/>  / \\     _\\o__</   "
	@echo "                 \\o/                                                                   \\o/                                                   "
	@echo "                  |                                                                     |                                                    "
	@echo "                 / \\                                                                   / \\                                                   "

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

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