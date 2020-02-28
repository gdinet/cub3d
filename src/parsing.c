/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 08:15:47 by gdinet            #+#    #+#             */
/*   Updated: 2020/02/28 10:54:48 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

#include <unistd.h>
#include <stdio.h>

int		parse_res(t_map *map, char *line, t_mlx *mlx)
{
	if (*line != ' ')
		return (0);			//error msg
	while (*line == ' ')
		line++;
	map->res_x = ft_atoi(line);
	while (*line >= '0' && *line <= '9')
		line++;
	map->res_y = ft_atoi(line);
	if (map->res_x <= 0 || map->res_y <= 0)
		return (0);			//error msg
	if (map->res_x > RES_X_MAX)
		map->res_x = RES_X_MAX;
	if (map->res_y > RES_Y_MAX)
		map->res_y = RES_Y_MAX;
	*mlx = init_mlx(map);
	return (1);
}

int		parse_texture(t_text *text, char *line, t_mlx *mlx)
{
	void	*img_ptr;
	int		bpp;
	int		endian;

	if (*line != ' ')
		exit(0);			//error msg
	while (*line == ' ')
		line++;
	img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, line, &text->width, &text->height);	//NULL si ' ' a la fin
	text->img = (int *)mlx_get_data_addr(img_ptr, &bpp, &text->size, &endian);			//verif si non NULL
	return (1);
}

int		parse_color(int *color, char *line)
{
	int r;
	int g;
	int b;

	if (*line != ' ')
		return (0);			//error msg
	while (*line == ' ')
		line++;
	r = ft_atoi(line);
	while (*line && *line != ',')
		line++;
	g = ft_atoi(++line);
	while (*line && *line != ',')
		line++;
	b = ft_atoi(++line);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);			//error msg
	*color = (r << 16) + (g << 8) + b;
	return (1);
}

int		parse_data(t_map *map, char *line, t_mlx *mlx)
{
	int		ret;

	ret = 0;
	if (*line == 'R')
		ret = parse_res(map, line + 1, mlx);
	else if (ft_strncmp(line, "NO", 2) == 0)
		ret = parse_texture(&map->north, line + 2, mlx);
	else if (ft_strncmp(line, "SO", 2) == 0)
		ret = parse_texture(&map->south, line + 2, mlx);
	else if (ft_strncmp(line, "EA", 2) == 0)
		ret = parse_texture(&map->east, line + 2, mlx);
	else if (ft_strncmp(line, "WE", 2) == 0)
		ret = parse_texture(&map->west, line + 2, mlx);
	else if (*line == 'F')
		ret = parse_color(&map->floor, line + 1);
	else if (*line == 'C')
		ret = parse_color(&map->ceil, line + 1);
	else if (*line == 'S')
		ret = parse_texture(&map->sprite, line + 1, mlx);
	else
		return (0);		//error msg
	return (ret);
}

int		parsing(t_map *map, t_mlx *mlx, int fd)
{
	char	*line;

	while (get_next_line(fd, &line) == 1)
	{
		if (*line == '1')
			parse_map(map, line);
		else if (*line)
		{
			if (!parse_data(map, line, mlx))
				return (0);
		}
		free(line);
	}
	parse_map(map, "");
	map->screen_d = (map->res_x / 2) / tan((float)FOV * M_PI / 360);
	return (1);
}
