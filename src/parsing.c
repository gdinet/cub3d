/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 08:15:47 by gdinet            #+#    #+#             */
/*   Updated: 2020/11/30 15:23:10 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

void	parse_res(t_param *param, char *line)
{
	if (param->map->res_x != 0 || param->map->res_y != 0)
		error_msg("Resolution already set", param);
	if (*line != ' ')
		error_msg("Unknown parameter", param);
	while (*line == ' ')
		line++;
	param->map->res_x = ft_atoi(line);
	while (*line >= '0' && *line <= '9')
		line++;
	param->map->res_y = ft_atoi(line);
	if (param->map->res_x <= 0 || param->map->res_y <= 0)
		error_msg("Resolution can't be negative", param);
	if (param->map->res_x > RES_X_MAX)
		param->map->res_x = RES_X_MAX;
	if (param->map->res_y > RES_Y_MAX)
		param->map->res_y = RES_Y_MAX;
	init_win(param);
}

void	parse_texture(t_text *text, char *line, t_param *p)
{
	int		bpp;
	int		endian;

	if (text->img != NULL)
		error_msg("Texture already set", p);
	if (*line != ' ')
		error_msg("Unknown parameter", p);
	while (*line == ' ')
		line++;
	text->ptr = mlx_xpm_file_to_image(p->mlx->mlx_ptr, line, &text->width,
	&text->height);
	if (text->ptr)
		text->img = (int *)mlx_get_data_addr(text->ptr, &bpp, &text->size,
		&endian);
}

void	parse_color(int *color, char *line, t_param *param)
{
	int r;
	int g;
	int b;

	if (*color != -1)
		error_msg("Color already set", param);
	if (*line != ' ')
		error_msg("Unknown parameter", param);
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
		error_msg("Color must be in range [0:255]", param);
	*color = (r << 16) + (g << 8) + b;
}

void	parse_data(t_param *param, char *line)
{
	while (ft_isspace(*line))
		line++;
	if (*line == 'R')
		parse_res(param, line + 1);
	else if (ft_strncmp(line, "NO", 2) == 0)
		parse_texture(&param->map->north, line + 2, param);
	else if (ft_strncmp(line, "SO", 2) == 0)
		parse_texture(&param->map->south, line + 2, param);
	else if (ft_strncmp(line, "EA", 2) == 0)
		parse_texture(&param->map->east, line + 2, param);
	else if (ft_strncmp(line, "WE", 2) == 0)
		parse_texture(&param->map->west, line + 2, param);
	else if (*line == 'F')
		parse_color(&param->map->floor, line + 1, param);
	else if (*line == 'C')
		parse_color(&param->map->ceil, line + 1, param);
	else if (*line == 'S')
		parse_texture(&param->map->sprite, line + 1, param);
	else
		error_msg("Unknown parameter", param);
}

void	parsing(t_param *p, int fd)
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
				check_data(p);
				in_map = 1;
			}
			if (in_map)
				parse_map(p, line);
			else
				parse_data(p, line);
		}
		free(line);
	}
	parse_map(p, NULL);
	check_map(p->map->map, p);
	p->map->screen_d = (p->map->res_x / 2) / tan((float)FOV * M_PI / 360);
	if (!(p->map->dist_array = malloc(sizeof(float) * p->map->res_x)))
		error_msg("Malloc error", p);
}
