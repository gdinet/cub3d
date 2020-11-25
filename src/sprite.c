/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:32:30 by gdinet            #+#    #+#             */
/*   Updated: 2020/11/25 16:28:31 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"
#include <math.h>

#define SPRITE 0x330000
#define SPRITE_SIZE 0.5

void	sprite_dist(float x, float y, t_list *lst_sprite)
{
	t_list		*tmp;
	t_sprite	*sprite;

	tmp = lst_sprite;
	while (tmp)
	{
		sprite = tmp->content;
		sprite->dist = sqrt(pow(x - sprite->pos_x, 2) +
		pow(y - sprite->pos_y, 2));
		tmp = tmp->next;
	}
}

int		cmp_sprite(t_sprite *s1, t_sprite *s2)
{
	if (s1->dist >= s2->dist)
		return (0);
	return (1);
}

void	sort_sprite(float x, float y, t_list *lst_sprite)
{
	t_list		*tmp;
	t_sprite	*sprite;

	sprite_dist(x, y, lst_sprite);
	tmp = lst_sprite;
	while (tmp && tmp->next)
	{
		if (cmp_sprite(tmp->content, tmp->next->content))
		{
			sprite = tmp->content;
			tmp->content = tmp->next->content;
			tmp->next->content = sprite;
			tmp = lst_sprite;
		}
		else
			tmp = tmp->next;
	}
}

int		sprite_color(t_text *sprite, float i, float j, float size)
{
	int		coord_x;
	int		coord_y;
	int		color;

	coord_x = i / size * sprite->width;
	coord_y = j / size * sprite->height;
	color = sprite->img[(sprite->size * coord_y / 4) + coord_x];
	return (color);
}

void	print_sprite(t_map *map, t_sprite *sprite, t_mlx *mlx)
{
	float	angle;
	float	size;
	float	col;
	int		i;
	int		j;
	int		color;

	angle = (atan2(sprite->pos_y - map->pos_y,
	sprite->pos_x - map->pos_x) * 180 / M_PI) - map->angle;
	if (angle < -180)
		angle += 360;
	size = map->screen_d * SPRITE_SIZE / (cos(angle * M_PI / 180) *
	sprite->dist);
	col = tan(angle * M_PI / 180) * map->screen_d;
	i = fmax((map->res_x / 2 + col - size / 2), 0);
	while (i < map->res_x / 2 + col + size / 2 && i < map->res_x)
	{
		if (sprite->dist < map->dist_array[i])
		{
			j = fmax((map->res_y - size) / 2, 0);
			while (j < (map->res_y + size) / 2 && j < map->res_y)
			{
				color = sprite_color(&map->sprite, i - (map->res_x / 2 + col - size / 2),
				j - (map->res_y - size) / 2, size);
				if (color)
					mlx->img[(mlx->size * j / 4) + i] = color;
				j++;
			}
		}
		i++;
	}
}
