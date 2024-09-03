# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/29 14:35:19 by hben-laz          #+#    #+#              #
#    Updated: 2024/08/31 13:25:57 by hben-laz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror 

RM = rm -f

SRC =  philo.c parse.c strtim.c outils.c destroy.c initialize.c action.c routine.c

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