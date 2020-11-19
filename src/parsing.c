/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 08:15:47 by gdinet            #+#    #+#             */
/*   Updated: 2020/11/10 16:20:25 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

#include <unistd.h>
#include <stdio.h>

void	error_msg(char *str)			//a bouger
{
	printf("%s", str);					//printf
	exit(0);
}

void	parse_res(t_map *map, char *line, t_mlx *mlx)
{
	if (map->res_x != 0 || map->res_y != 0)
		error_msg("error 1\n");			//msg
	if (*line != ' ')
		error_msg("error 2\n");			//error msg
	while (*line == ' ')
		line++;
	map->res_x = ft_atoi(line);
	while (*line >= '0' && *line <= '9')
		line++;
	map->res_y = ft_atoi(line);
	if (map->res_x <= 0 || map->res_y <= 0)
		error_msg("error 3\n");			//error msg
	if (map->res_x > RES_X_MAX)
		map->res_x = RES_X_MAX;
	if (map->res_y > RES_Y_MAX)
		map->res_y = RES_Y_MAX;
	init_win(map, mlx);
}

void	parse_texture(t_text *text, char *line, t_mlx *mlx)
{
	void	*img_ptr;
	int		bpp;
	int		endian;

	if (text->img != NULL)
		error_msg("error 4\n");				//error msg
	if (*line != ' ')
		error_msg("error 5\n");			//error msg
	while (*line == ' ')
		line++;
	img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, line, &text->width, &text->height);	//NULL si ' ' a la fin
	text->img = (int *)mlx_get_data_addr(img_ptr, &bpp, &text->size, &endian);			//verif si non NULL
}

void	parse_color(int *color, char *line)
{
	int r;
	int g;
	int b;

	if (*color != -1)
		error_msg("error 6\n");				//msg
	if (*line != ' ')
		error_msg("error 7\n");			//error msg
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
		error_msg("error 8\n");			//error msg
	*color = (r << 16) + (g << 8) + b;
}

void	parse_data(t_map *map, char *line, t_mlx *mlx)
{
	if (*line == 'R')
		parse_res(map, line + 1, mlx);
	else if (ft_strncmp(line, "NO", 2) == 0)
		parse_texture(&map->north, line + 2, mlx);
	else if (ft_strncmp(line, "SO", 2) == 0)
		parse_texture(&map->south, line + 2, mlx);
	else if (ft_strncmp(line, "EA", 2) == 0)
		parse_texture(&map->east, line + 2, mlx);
	else if (ft_strncmp(line, "WE", 2) == 0)
		parse_texture(&map->west, line + 2, mlx);
	else if (*line == 'F')
		parse_color(&map->floor, line + 1);
	else if (*line == 'C')
		parse_color(&map->ceil, line + 1);
	else if (*line == 'S')
		parse_texture(&map->sprite, line + 1, mlx);
	else
		error_msg("error 9\n");		//error msg
}

void	parsing(t_map *map, t_mlx *mlx, int fd)
{
	char	*line;
	int		in_map;

	in_map = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (*line)
		{
			if (!in_map && is_map(line))
			{
				check_data(map);
				in_map = 1;
			}
			if (in_map)
				parse_map(map, line);
			else
				parse_data(map, line, mlx);
		}
		free(line);
	}
	parse_map(map, NULL);
	check_map(map->map);
	map->screen_d = (map->res_x / 2) / tan((float)FOV * M_PI / 360);
	if (!(map->dist_array = malloc(sizeof(float) * map->res_x)))
		error_msg("error 17\n");
}
