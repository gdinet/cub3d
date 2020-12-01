/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 10:56:11 by gdinet            #+#    #+#             */
/*   Updated: 2020/12/01 17:09:16 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

float	horizontal_hit(t_map *map, t_calc *calc)
{
	float	pos;

	if (calc->side_hit == 0)
		pos = map->pos_y + calc->side_x * calc->dir_y;
	else
		pos = map->pos_x + calc->side_y * calc->dir_x;
	return (pos - floor(pos));
}

float	vertical_hit(t_map *map, int line, int wall_h)
{
	float	pos;

	pos = line - (map->res_y / 2 - wall_h / 2);
	pos = pos / wall_h;
	return (pos);
}

int		get_color(t_text *text, float i, float j)
{
	int		coord_x;
	int		coord_y;

	coord_x = i * text->width;
	coord_y = j * text->height;
	return (text->img[(text->size * coord_y / 4) + coord_x]);
}
