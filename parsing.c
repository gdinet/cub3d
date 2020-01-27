/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 08:15:47 by gdinet            #+#    #+#             */
/*   Updated: 2020/01/27 10:59:00 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d.h"
#include "libft.h"

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int		parse_res(t_data *data, char *line)
{
	if (*line != ' ')
		return (0);			//error msg
	while (*line == ' ')
		line++;
	data->res_x = ft_atoi(line);
	while (*line >= '0' && *line <= '9')
		line++;
	data->res_y = ft_atoi(line);
	if (data->res_x <= 0 || data->res_y <= 0)
		return (0);			//error msg
	if (data->res_x > RES_X_MAX)
		data->res_x = RES_X_MAX;
	if (data->res_y > RES_Y_MAX)
		data->res_y = RES_Y_MAX;
	return (1);
}

int		parse_texture(char **texture, char *line)
{
	if (*line != ' ')
		return (0);			//error msg
	while (*line == ' ')
		line++;
	if (!(*texture = ft_strdup(line)))
		return (0);			//error msg
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

int		parse_data(t_data *data, char *line)
{
	int		ret;

	ret = 0;
	if (*line == 'R')
		ret = parse_res(data, line + 1);
	else if (ft_strncmp(line, "NO", 2) == 0)
		ret = parse_texture(&data->north, line + 2);
	else if (ft_strncmp(line, "SO", 2) == 0)
		ret = parse_texture(&data->south, line + 2);
	else if (ft_strncmp(line, "EA", 2) == 0)
		ret = parse_texture(&data->east, line + 2);
	else if (ft_strncmp(line, "WE", 2) == 0)
		ret = parse_texture(&data->west, line + 2);
	else if (*line == 'F')
		ret = parse_color(&data->floor, line + 1);
	else if (*line == 'C')
		ret = parse_color(&data->ceil, line + 1);
	else if (*line == 'S')
		ret = parse_texture(&data->sprite, line + 1);
	else
		return (0);		//error msg
	return (ret);
}

int		parsing(t_data *data, int fd)
{
	char	*line;

	while (get_next_line(fd, &line) == 1)
	{
		if (*line == '1')
			parse_map(data, line);
		else if (*line)
		{
			if (!parse_data(data, line))
				return (0);
		}
		free(line);
	}
	parse_map(data, "");
	return (1);
}

int main(int ac, char **av)
{
	int fd;
	t_data	data;
	int i = 0;

	fd = open(av[1], O_RDONLY);
	parsing(&data, fd);
	close (fd);
	printf("res x : %d, res y : %d\ntext no : %s\ntext so : %s\ntext ea : %s\ntext we : %s\n",
			data.res_x, data.res_y, data.north, data.south, data.east, data.west);
	printf("color c : %x\ncolor f : %x\ntext s : %s\n", data.ceil, data.floor, data.sprite);
	printf("pos x: %.1f, pos y : %.1f, angle : %.1f\n", data.pos_x, data.pos_y, data.angle);
	while (data.map[i])
	{
		printf("%s\n", data.map[i]);
		i++;
	}
	return 0;
}
