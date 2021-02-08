/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 09:33:00 by gdinet            #+#    #+#             */
/*   Updated: 2021/02/08 16:04:01 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"
#include "mlx.h"

void		init_calc(t_calc *calc, t_map *map)
{
	calc->delta_x = fabs(1 / calc->dir_x);
	calc->delta_y = fabs(1 / calc->dir_y);
	if (calc->dir_x < 0.0)
	{
		calc->step_x = -1;
		calc->side_x = (map->pos_x - floor(map->pos_x)) * calc->delta_x;
	}
	else
	{
		calc->step_x = 1;
		calc->side_x = (ceil(map->pos_x) - map->pos_x) * calc->delta_x;
	}
	if (calc->dir_y < 0.0)
	{
		calc->step_y = -1;
		calc->side_y = (map->pos_y - floor(map->pos_y)) * calc->delta_y;
	}
	else
	{
		calc->step_y = 1;
		calc->side_y = (ceil(map->pos_y) - map->pos_y) * calc->delta_y;
	}
}

void		print_col(t_param *p, t_dir dir, int col, float h_hit)
{
	int		line;
	int		color;
	int		wall_h;
	float	v_hit;

	line = 0;
	wall_h = (1 / p->map->dist_array[col]) * p->map->screen_d;
	while (line < p->map->res_y)
	{
		v_hit = vertical_hit(p->map, line, wall_h);
		if (line > p->map->res_y / 2 + wall_h / 2)
			color = p->map->floor;
		else if (line < p->map->res_y / 2 - wall_h / 2)
			color = p->map->ceil;
		else if (dir == east)
			color = get_color(&p->map->east, h_hit, v_hit);
		else if (dir == west)
			color = get_color(&p->map->west, h_hit, v_hit);
		else if (dir == south)
			color = get_color(&p->map->south, h_hit, v_hit);
		else if (dir == north)
			color = get_color(&p->map->north, h_hit, v_hit);
		p->mlx->img[(p->mlx->size * line / 4) + col] = color;
		line++;
	}
}

void		print_wall(t_calc *calc, t_param *p, int col)
{
	t_dir	dir;
	float	dist;
	float	diff_angle;

	diff_angle = (calc->angle - p->map->angle) * M_PI / 180;
	if (calc->side_hit == 0)
	{
		dist = calc->side_x * cos(diff_angle);
		dir = (calc->step_x == 1) ? east : west;
	}
	else
	{
		dist = calc->side_y * cos(diff_angle);
		dir = (calc->step_y == 1) ? south : north;
	}
	p->map->dist_array[col] = dist;
	print_col(p, dir, col, horizontal_hit(p->map, calc));
}

void		dda(t_calc *calc, t_map *map)
{
	int		hit;
	int		x;
	int		y;

	x = (int)map->pos_x;
	y = (int)map->pos_y;
	hit = 0;
	while (!hit)
	{
		if (calc->side_x < calc->side_y)
		{
			calc->side_x += calc->delta_x;
			x += calc->step_x;
			calc->side_hit = 0;
		}
		else
		{
			calc->side_y += calc->delta_y;
			y += calc->step_y;
			calc->side_hit = 1;
		}
		hit = (map->map[y][x] == '1');
	}
	calc->side_x -= calc->delta_x;
	calc->side_y -= calc->delta_y;
}

int			render(t_param *p)
{
	float		a;
	float		delta_a;
	int			col;
	t_calc		calc;

	a = (p->map->angle < FOV / 2) ? p->map->angle - FOV / 2 + 360 :
	p->map->angle - FOV / 2;
	delta_a = (float)FOV / p->map->res_x;
	col = 0;
	while (col < p->map->res_x)
	{
		calc.angle = a;
		calc.dir_x = cos(a / 180 * M_PI);
		calc.dir_y = sin(a / 180 * M_PI);
		init_calc(&calc, p->map);
		dda(&calc, p->map);
		print_wall(&calc, p, col);
		a = (a + delta_a > 360) ? a + delta_a - 360 : a + delta_a;
		col++;
	}
	return (0);
}
