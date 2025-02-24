


NAME=philo

FLAGS = -Werror -Wall -Wextra

SRCS=philo.c\

OBJS=$(SRCS:.c=.o)
%.o:%.c
	cc $(FLAGS) -c $< -o checker


