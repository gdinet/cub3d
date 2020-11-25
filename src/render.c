/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 09:33:00 by gdinet            #+#    #+#             */
/*   Updated: 2020/11/25 15:34:14 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"
#include "mlx.h"

t_distance		init_dist(t_vector *ray)
{
	t_distance	dist;

	dist.delta_x = fabs(1 / ray->dir_x);
	dist.delta_y = fabs(1 / ray->dir_y);
	if (ray->dir_x < 0.0)
	{
		dist.step_x = -1;
		dist.side_x = (ray->pos_x - floor(ray->pos_x)) * dist.delta_x;
	}
	else
	{
		dist.step_x = 1;
		dist.side_x = (ceil(ray->pos_x) - ray->pos_x) * dist.delta_x;
	}
	if (ray->dir_y < 0.0)
	{
		dist.step_y = -1;
		dist.side_y = (ray->pos_y - floor(ray->pos_y)) * dist.delta_y;
	}
	else
	{
		dist.step_y = 1;
		dist.side_y = (ceil(ray->pos_y) - ray->pos_y) * dist.delta_y;
	}
	return (dist);
}

float			fish_eye(float dist, float angle_ray, float angle_cam)
{
	float	diff_angle;

	diff_angle = (angle_ray - angle_cam) * M_PI / 180;
	return (dist * cos(diff_angle));
}

void			print_wall(t_distance *dist, t_map *map, t_mlx *mlx, int col, float angle, t_vector *ray)
{
	int		color;
	float	distance;
	int		line;
	int		wall_height;
	float	hit;
	int		get;

	if (dist->side_hit == 0)
	{
		hit = wall_hit(dist, ray, dist->side_x);
		distance = fish_eye(dist->side_x, angle, map->angle);
		if (dist->step_x == 1)
			get = 1; //east
		else
			get = 2; //west
	}
	else
	{
		hit = wall_hit(dist, ray, dist->side_y);
		distance = fish_eye(dist->side_y, angle, map->angle);
		if (dist->step_y == 1)
			get = 3; //south
		else
			get = 4; //north
	}
	map->dist_array[col] = distance;
	wall_height = (1 / distance) * map->screen_d;
	line = 0;
	while (line < map->res_y)
	{
		if (line > map->res_y / 2 + wall_height / 2)
			mlx->img[(mlx->size * line / 4) + col] = map->ceil;
		else if (line < map->res_y / 2 - wall_height / 2)
			mlx->img[(mlx->size * line / 4) + col] = map->floor;
		else
		{
			if (get == 1)
				color = get_color(&map->east, line, wall_height, map, hit);
			else if (get == 2)
				color = get_color(&map->west, line, wall_height, map, hit);
			else if (get == 3)
				color = get_color(&map->south, line, wall_height, map, hit);
			else if (get == 4)
				color = get_color(&map->north, line, wall_height, map, hit);
			mlx->img[(mlx->size * line / 4) + col] = color;
		}
		line++;
	}
}

void		dda(t_vector *ray, t_map *map, t_mlx *mlx, int col)
{
	int			hit;
	int			x;
	int			y;
	t_distance	dist;

	dist = init_dist(ray);
	x = (int)map->pos_x;
	y = (int)map->pos_y;
	hit = 0;
	while (!hit)
	{
		if (dist.side_x < dist.side_y)
		{
			dist.side_x += dist.delta_x;
			x += dist.step_x;
			dist.side_hit = 0;
		}
		else
		{
			dist.side_y += dist.delta_y;
			y += dist.step_y;
			dist.side_hit = 1;
		}
		hit = (map->map[y][x] == '1');
	}
	dist.side_x -= dist.delta_x;
	dist.side_y -= dist.delta_y;
	print_wall(&dist, map, mlx, col, ray->angle, ray);
}

int		render(t_map *map, t_mlx *mlx)
{
	float		a;
	float		delta_a;
	int			col;
	t_vector	ray;

	a = (map->angle < FOV / 2) ? map->angle - FOV / 2 + 360 : map->angle - FOV / 2;
	delta_a = (float)FOV / map->res_x;
	ray.pos_x = map->pos_x;
	ray.pos_y = map->pos_y;
	col = 0;
	while (col < map->res_x)
	{
		ray.angle = a;
		ray.dir_x = cos(a / 180 * M_PI);
		ray.dir_y = sin(a / 180 * M_PI);
		dda(&ray, map, mlx, col);
		a = (a + delta_a > 360) ? a + delta_a - 360 : a + delta_a;
		col++;
	}
	return (0);
}
