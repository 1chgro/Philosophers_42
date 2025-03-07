NAME=philo

FLAGS = -Wall -Werror -Wextra -pthread

SRCS= mandatory/philo.c mandatory/philo_utils.c\
		mandatory/parse.c mandatory/init_dining_table.c
		
OBJS= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) mandatory/philo.h
	@cc $(FLAGS) $(OBJS) -o $(NAME)
	@echo "Done: excutable is ready"

%.o:%.c 
	@cc $(FLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS)
	@echo "Done:removing object files"

fclean: clean
	@rm -rf $(NAME)
	@echo "Done:removing excutable"

re: fclean all