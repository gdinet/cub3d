/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 09:33:00 by gdinet            #+#    #+#             */
/*   Updated: 2020/02/26 14:39:16 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"
#include "mlx.h"

#include <stdio.h>

t_distance		init_dist(t_vector *ray)
{
	t_distance	dist;

	dist.delta_x = sqrt(1 + (ray->dir_y * ray->dir_y) / (ray->dir_x * ray->dir_x));
	dist.delta_y = sqrt(1 + (ray->dir_x * ray->dir_x) / (ray->dir_y * ray->dir_y));
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

void			print_wall(t_distance *dist, t_map *map, t_mlx *mlx, int col, float angle)
{
	unsigned int		color;
	float				distance;
	int					line;
	int					high;

	if (dist->side_hit == 0)
	{
		distance = fish_eye(dist->side_x - dist->delta_x, angle, map->angle);
		if (dist->step_x == 1)
			color = EAST_COLOR;
		else
			color = WEST_COLOR;
	}
	else
	{
		distance = fish_eye(dist->side_y - dist->delta_y, angle, map->angle);
		if (dist->step_y == 1)
			color = SOUTH_COLOR;
		else
			color = NORTH_COLOR;
	}
	high = (WALL_H / distance) * map->screen_d;
	line = 0;
	while (line < map->res_y)
	{
		if (line > map->res_y / 2 + high / 2)
			mlx->img[(mlx->size * line / 4) + col] = map->ceil;
		else if (line < map->res_y / 2 - high / 2)
			mlx->img[(mlx->size * line / 4) + col] = map->floor;
		else
			mlx->img[(mlx->size * line / 4) + col] = color;
		line++;
	}
}

void			dda(t_vector *ray, t_map *map, t_mlx *mlx, int col, float angle)
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
			dist.side_hit= 1;
		}
		hit = (map->map[y][x] != '0');
	}
	print_wall(&dist, map, mlx, col, angle);
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
		ray.dir_x = cos(a / 180 * M_PI);
		ray.dir_y = sin(a / 180 * M_PI);
		dda(&ray, map, mlx, col, a);
		a = (a + delta_a > 360) ? a + delta_a - 360 : a + delta_a;
		col++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img_ptr, 0, 0);
	return (0);
}
