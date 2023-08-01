# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/22 15:12:28 by huolivei          #+#    #+#              #
#    Updated: 2023/03/28 11:52:09 by huolivei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_m
SRC = philo/src/destroy_join_one.c philo/src/eat_sleep_think_die.c \
		philo/src/initialize.c philo/src/main.c philo/src/routine_checker.c philo/src/utils.c
OBJ = $(SRC:.c=.o)
INC = philo/inc/phy.h
CC = cc -g
FLAGS = -Wall -Wextra -Werror -pthread
RM = rm

all: $(NAME)

$(NAME): $(OBJ) $(INC)
	$(CC) $(FLAGS) -I $(INC) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
