# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: feedme <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/15 17:57:17 by feedme            #+#    #+#              #
#    Updated: 2018/10/26 13:52:43 by feedme           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = grimly

FLAGS = -Wall -Wextra -Werror
SRC = srcs/*.c
OBJ = $(patsubst %.c,%.o,$(SRC))
LIB = libft.a libftprintf.a

all: $(NAME)

$(NAME):
	gcc $(FLAGS) $(SRC) $(LIB) -o $(NAME)

lldb:
	gcc $(FLAGS) $(SRC) $(LIB) -o $(NAME) -g

clean:
	rm -rf *.o

fclean: clean
	rm $(NAME)
	rm -rf $(NAME).dSYM

re: fclean all
