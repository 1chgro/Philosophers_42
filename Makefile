NAME=philo

FLAGS = -Werror -Wall -Wextra -fsanitize=thread -g

SRCS=philo.c

OBJS= $(SRCS:.c=.o)

NAME: $(OBJS)
	@cc $(FLAGS) -pthread $(OBJS) -o $(NAME)
	@echo "Done: excutable is ready"

%.o:%.c
	@cc $(FLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS)
	@echo "Done:removing object files"

fclean: clean
	@rm -rf $(NAME)
	@echo "Done:removing excutable"

