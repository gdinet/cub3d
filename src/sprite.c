/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:32:30 by gdinet            #+#    #+#             */
/*   Updated: 2020/12/01 17:31:44 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"
#include <math.h>

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

void	sprite_loop(t_param *p, float dist, float col, float size)
{
	int				i;
	int				j;
	unsigned int	color;

	i = fmax((p->map->res_x / 2 + col - size / 2), 0);
	while (i < p->map->res_x / 2 + col + size / 2 && i < p->map->res_x)
	{
		if (dist < p->map->dist_array[i])
		{
			j = fmax((p->map->res_y - size) / 2, 0);
			while (j < (p->map->res_y + size) / 2 && j < p->map->res_y)
			{
				color = sprite_color(&p->map->sprite, i - (p->map->res_x / 2 +
				col - size / 2), j - (p->map->res_y - size) / 2, size);
				if (color != 0xff000000)
					p->mlx->img[(p->mlx->size * j / 4) + i] = color;
				j++;
			}
		}
		i++;
	}
}

void	print_sprite(t_param *p, t_sprite *sprite)
{
	float			angle;
	float			size;
	float			col;

	angle = (atan2(sprite->pos_y - p->map->pos_y,
	sprite->pos_x - p->map->pos_x) * 180 / M_PI) - p->map->angle;
	if (angle < -180)
		angle += 360;
	size = p->map->screen_d / (cos(angle * M_PI / 180) *
	sprite->dist);
	col = tan(angle * M_PI / 180) * p->map->screen_d;
	sprite_loop(p, sprite->dist, col, size);
}

void	sprite(t_param *p)
{
	t_list	*tmp;

	sort_sprite(p->map->pos_x, p->map->pos_y, p->map->lst_sprite);
	tmp = p->map->lst_sprite;
	while (tmp)
	{
		print_sprite(p, tmp->content);
		tmp = tmp->next;
	}
}
