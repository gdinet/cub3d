/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 09:16:47 by gdinet            #+#    #+#             */
/*   Updated: 2020/11/09 15:10:28 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <stdio.h>

void	move_straight(t_key key, t_map *map)
{
	float	dir;
	float	angle_r;

	angle_r = map->angle / 180.0 * M_PI;
	if ((key & W) && !(key & S))
		dir = 0.1;
	else if ((key & S) && !(key & W))
		dir = -0.1;
	else
		dir = 0.0;
	if (map->map[(int)map->pos_y][(int)(map->pos_x + dir * cos(angle_r))] == '0')
		map->pos_x += dir * cos(angle_r);
	if (map->map[(int)(map->pos_y + dir * sin(angle_r))][(int)map->pos_x] == '0')
		map->pos_y += dir * sin(angle_r);
}

void	move_side(t_key key, t_map *map)
{
	float	dir;
	float	angle_r;

	angle_r = (map->angle + 90) / 180.0 * M_PI;
	if ((key & A) && !(key & D))
		dir = -0.1;
	else if ((key & D) && !(key & A))
		dir = 0.1;
	else
		dir = 0.0;
	if (map->map[(int)map->pos_y][(int)(map->pos_x + dir * cos(angle_r))] == '0')
		map->pos_x += dir * cos(angle_r);
	if (map->map[(int)(map->pos_y + dir * sin(angle_r))][(int)map->pos_x] == '0')
		map->pos_y += dir * sin(angle_r);
}

void	rotate(t_key key, t_map *map)
{
	int		dir;

	if ((key & RIGHT) && !(key & LEFT))
		dir = 2;
	else if ((key & LEFT) && !(key & RIGHT))
		dir = -2;
	else
		dir = 0;
	map->angle += dir;
	if (map->angle > 360.0)
		map->angle -= 360.0;
	else if (map->angle < 0.0)
		map->angle += 360.0;
}
