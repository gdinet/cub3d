/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 14:51:30 by gdinet            #+#    #+#             */
/*   Updated: 2021/02/10 13:12:21 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void	bmp_header(int fd, t_map *map, t_mlx *mlx)
{
	int		offset;
	int		file_size;
	int		header_size;
	int		color_plane;
	int		image_size;

	offset = 54;
	file_size = offset + (4 * map->res_x * map->res_y);
	header_size = 40;
	color_plane = 1;
	image_size = map->res_x * map->res_y;
	write(fd, "BM", 2);
	write(fd, &file_size, 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, &offset, 4);
	write(fd, &header_size, 4);
	write(fd, &map->res_x, 4);
	write(fd, &map->res_y, 4);
	write(fd, &color_plane, 2);
	write(fd, &mlx->bpp, 2);
	write(fd, "\0\0\0\0", 4);
	write(fd, &image_size, 4);
	write(fd, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 16);
}

void	bmp_image(int fd, t_map *map, t_mlx *mlx)
{
	int		x;
	int		y;
	int		color;

	y = map->res_y - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < map->res_x)
		{
			color = mlx->img[(mlx->size * y / 4) + x];
			write(fd, &color, 4);
			x++;
		}
		y--;
	}
}

void	bmp_file(t_param *p)
{
	int		fd;

	p->mlx->img_ptr = mlx_new_image(p->mlx->mlx_ptr, p->map->res_x,
	p->map->res_y);
	p->mlx->img = (int *)mlx_get_data_addr(p->mlx->img_ptr,
	&p->mlx->bpp, &p->mlx->size, &p->mlx->endian);
	render(p);
	sprite(p);
	fd = open("cub3d.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0755);
	bmp_header(fd, p->map, p->mlx);
	bmp_image(fd, p->map, p->mlx);
	close(fd);
	close_window(p);
}
