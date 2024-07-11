NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror 

RM = rm -f

SRC =  philo.c 

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -I. $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c philo.h
		 $(CC) -I. $(CFLAGS) -c $< -o $@


clean:
		$(RM) $(OBJ) 

fclean: clean
		$(RM) $(NAME)
 
re: fclean all