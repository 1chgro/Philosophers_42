NAME=philo

FLAGS = -pthread -fsanitize=thread -g

SRCS=mandatory/philo.c mandatory/philo_utils.c mandatory/parse.c

OBJS= $(SRCS:.c=.o)


NAME: $(OBJS) mandatory/philo.h
	@cc $(FLAGS) $( OBJS) -o $(NAME)
	@echo "Done: excutable is ready"

all: $(NAME)

%.o:%.c 
	@cc $(FLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS)
	@echo "Done:removing object files"

fclean: clean
	@rm -rf $(NAME)
	@echo "Done:removing excutable"


re: fclean all