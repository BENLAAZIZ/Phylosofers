NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -fsanitize=thread

RM = rm -f

SRC =  philo.c parse.c strtim.c 

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c philo.h
		 $(CC) $(CFLAGS) -c $< -o $@


clean:
		$(RM) $(OBJ) 

fclean: clean
		$(RM) $(NAME)
 
re: fclean all