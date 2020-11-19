/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 10:56:11 by gdinet            #+#    #+#             */
/*   Updated: 2020/11/19 16:58:18 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

float	wall_hit(t_distance *dist, t_vector *ray, float distance)
{
	float	pos;

	if (dist->side_hit == 0)
		pos = ray->pos_y + distance * ray->dir_y;
	else
		pos = ray->pos_x + distance * ray->dir_x;
	return (pos - floor(pos));
}

int		get_color(t_text *text, int line, int wall_h, t_map *map, float hit)
{
	int		coord_x;
	int		coord_y;
	int		color;
	float	pos_y;

	coord_x = (int)(hit * text->width);
	pos_y = (text->height / 2) * (map->res_y / 2 - line) / (wall_h / 2);
	if (line > map->res_y / 2)
		pos_y = -pos_y + text->height / 2;
	else
		pos_y = text->height / 2 - pos_y;
	coord_y = (int)pos_y;
	color = text->img[(text->size * coord_y / 4) + coord_x];
	return (color);
}
