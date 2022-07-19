MANDATORY= philosophers.c function_libft.c
BONUS= 

CC=cc
FLAGS= -Wall -Werror -Wextra -pthread
DEBUG=-fsanitize=address -g
NAME=philo
PIP=philo_bonus

O_MANDATORY=$(MANDATORY:%.c=%.o)
O_BONUS=$(BONUS:%.c=%.o)

all: $(NAME)

$(NAME):
	gcc $(FLAGS) $(MANDATORY) -o $(NAME)

bonus: $(VRGET_NEXT) $(PIP)

$(PIP):
	gcc $(FLAGS) $(BONUS) $(DEBUG)  -o $(PIP) -g

debug:
	gcc $(FLAGS) $(DEBUG) $(PIP) $(MANDATORY) -o $(NAME)

clean:
	rm -rf *.o

fclean:
	rm -rf *.o $(NAME) $(PIP)

re: fclean all