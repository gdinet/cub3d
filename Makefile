# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/21 15:11:17 by gdinet            #+#    #+#              #
#    Updated: 2020/11/09 17:03:12 by gdinet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= gcc

CFLAG		= -Wall -Wextra -Werror -I $(INC)

FT			:= libft
MLX			:= minilibx-linux

INC			= ./inc

SRC			= src/map_parsing.c \
			  src/parsing.c \
			  src/check.c \
			  src/render.c \
			  src/init.c \
			  src/events.c \
			  src/texture.c \
			  src/sprite.c \
			  src/main.c

OBJ			= $(SRC:%.c=%.o)

NAME		= cub3d

all:		minilibx $(NAME)

libft:
			make -C $(FT)

minilibx:
			make -C $(MLX)
			cp $(MLX)/libmlx.a ./
			cp $(MLX)/mlx.h $(INC)

$(NAME):	$(OBJ)
			make -C $(FT)
			$(CC) $(CFLAG) -o $@ $(OBJ) -L./libft -lft -l mlx -lX11 -lXext -lbsd -lm

.c.o:
			$(CC) $(CFLAG) -c $< -o $(<:.c=.o)

clean:
			make -C $(FT) $@
			make -C $(MLX) $@
			rm -f $(OBJ)

fclean:		clean
			make -C $(FT) $@
			rm -f libmlx.a
			rm -f $(INC)/mlx.h
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
