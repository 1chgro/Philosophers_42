NAME=philo_bonus

FLAGS = -Wall -Werror -Wextra -pthread -fsanitize=thread -g

SRCS= \
		philo_bonus.c\
		parse_bonus.c\
		bonus_utils.c
		
OBJS= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) philo_bonus.h
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