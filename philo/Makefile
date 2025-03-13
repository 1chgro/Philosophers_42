NAME = philo

FLAGS = -Wall -Werror -Wextra -pthread

SRCS = \
		philo.c\
		parse.c\
		routine.c\
		monitor.c\
		philo_utils.c\
		init_dining_table.c
		
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) philo.h
	@cc $(FLAGS) $(OBJS) -o $(NAME)
	@echo "Done: executable is ready"

%.o:%.c 
	@cc $(FLAGS) -c $< -o $@ 

clean:
	@rm -rf $(OBJS)
	@echo "Done:removing object files"

fclean: clean
	@rm -rf $(NAME)
	@echo "Done:removing excutable"

re: fclean all