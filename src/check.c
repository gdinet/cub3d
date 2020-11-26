/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 11:12:26 by gdinet            #+#    #+#             */
/*   Updated: 2020/11/26 15:46:09 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <stdlib.h>

void	check_data(t_param *param)
{
	if (param->map->res_x == 0 || param->map->res_y == 0)
		error_msg("Resolution not set", param);
	if (param->map->north.img == NULL || param->map->south.img == NULL ||
	param->map->west.img == NULL || param->map->east.img == NULL ||
	param->map->sprite.img == NULL)
		error_msg("Texture not set", param);
	if (param->map->floor == -1 || param->map->ceil == -1)
		error_msg("Floor or ceil color not set", param);
}

int		is_map(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || (line[i] >= '0' && line[i] <= '9') ||
		line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
			i++;
		else
			return (0);
	}
	return (1);
}

int		is_open(char **map, int i, int j)
{
	int		len_prev;
	int		len_next;

	if (i == 0 || j == 0)
		return (1);
	if (map[i + 1] == NULL || map[i][j + 1] == '\0')
		return (1);
	len_prev = ft_strlen(map[i - 1]);
	len_next = ft_strlen(map[i + 1]);
	if (len_prev < j || len_next < j)
		return (1);
	if (map[i][j - 1] == ' ' || map[i][j + 1] == ' ' ||
			map[i - 1][j] == ' ' || map[i + 1][j] == ' ')
		return (1);
	return (0);
}

void	check_map(char **map, t_param *param)
{
	int		i;
	int		j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != ' ' && is_open(map, i, j))
				error_msg("Map not closed", param);
			j++;
		}
		i++;
	}
}
