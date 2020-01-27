# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/21 15:11:17 by gdinet            #+#    #+#              #
#    Updated: 2019/11/22 14:41:03 by gdinet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= gcc

CFLAG		= -Wall -Wextra -Werror -I ./inc

SRC			= src/display.c \
			  src/distance.c \
			  src/wall_distance.c \
			  src/main.c

OBJ			= $(SRC:%.c=%.o)

NAME		= cub3d

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) -o $@ $(OBJ) -L. -lmlx -framework OpenGL -framework AppKit -lm

.c.o:
			$(CC) $(CFLAG) -c $< -o $(<:.c=.o)

clean:
			rm -rf $(OBJ)

fclean:		clean
			rm $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
