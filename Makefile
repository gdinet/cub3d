# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/21 15:11:17 by gdinet            #+#    #+#              #
#    Updated: 2020/03/04 14:08:56 by gdinet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= gcc

CFLAG		= -Wall -Wextra -Werror -I ./inc

SRC			= src/map_parsing.c \
			  src/parsing.c \
			  src/check.c \
			  src/render.c \
			  src/init.c \
			  src/events.c \
			  src/texture.c \
			  src/main.c

OBJ			= $(SRC:%.c=%.o)

NAME		= cub3d

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) -o $@ $(OBJ) -L./libft -lft -l mlx -framework OpenGL -framework AppKit

.c.o:
			$(CC) $(CFLAG) -c $< -o $(<:.c=.o)

clean:
			rm -rf $(OBJ)

fclean:		clean
			rm $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
