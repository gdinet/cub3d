/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 11:26:10 by gdinet            #+#    #+#             */
/*   Updated: 2020/03/04 15:04:46 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "cub3d.h"

#include <stdio.h>

void	add_to_list(char *line, t_list **map_list)
{
	char	*str;

	if (!is_map(line))
		error_msg("error");					//msg
	if (!(str = ft_strdup(line)))
		error_msg("error\n");				//error msg
	ft_lstadd_back(map_list, ft_lstnew(str));
}

int		list_to_array(t_list *map_list, t_map *map)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = map_list;
	if (!(map->map = malloc(sizeof(char *) * (ft_lstsize(map_list) + 1))))
		return (0);
	while (tmp)
	{
		map->map[i] = tmp->content;
		i++;
		tmp = tmp->next;
	}
	map->map[i] = NULL;
	return (1);
}

void	pos_player(t_map *map)
{
	int		x;
	int		y;

	y = -1;
	while (map->map[++y])
	{
		x = -1;
		while (map->map[y][++x])
		{
			if (ft_isalpha(map->map[y][x]))				//verif non attribue
			{
				if (map->map[y][x] == 'N' || map->map[y][x] == 'S')
					map->angle = (map->map[y][x] == 'S') ? 90.0 : 270.0;
				if (map->map[y][x] == 'E' || map->map[y][x] == 'W')
					map->angle = (map->map[y][x] == 'E') ? 0.0 : 180.0;
				map->map[y][x] = '0';
				map->pos_x = x + 0.5;
				map->pos_y = y + 0.5;
			}
		}
	}
}

void	parse_map(t_map *map, char *line)
{
	static t_list	*map_list = NULL;

	if (line)
		add_to_list(line, &map_list);
	else
	{
		if (!list_to_array(map_list, map))
			error_msg("error\n");			//error msg
		ft_lstclear(&map_list, NULL);
		pos_player(map);
	}
}
