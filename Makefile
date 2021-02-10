# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/21 15:11:17 by gdinet            #+#    #+#              #
#    Updated: 2021/02/11 00:52:39 by gdinet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= gcc

CFLAG		= -Wall -Wextra -Werror $(INC)

FT			:= libft
MLX			:= minilibx-linux

INC			= -I./inc -I./$(MLX)

SRC			= src/map_parsing.c \
			  src/parsing.c \
			  src/check.c \
			  src/render.c \
			  src/init.c \
			  src/events.c \
			  src/texture.c \
			  src/sort_sprite.c \
			  src/sprite.c \
			  src/bitmap.c \
			  src/end.c \
			  src/main.c

OBJ			= $(SRC:%.c=%.o)

NAME		= cub3d

all:		minilibx $(NAME)

libft:
			make -C $(FT)

minilibx:
			make -C $(MLX)

$(NAME):	$(OBJ)
			make -C $(FT)
			$(CC) $(CFLAG) -o $@ $(OBJ) -L./$(FT) -lft -lmlx -lX11 -lXext -lbsd -lm

.c.o:
			$(CC) $(CFLAG) -c $< -o $(<:.c=.o)

clean:
			make -C $(FT) $@
			make -C $(MLX) $@
			rm -f $(OBJ)

fclean:		clean
			make -C $(FT) $@
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
