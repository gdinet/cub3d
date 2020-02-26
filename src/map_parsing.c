/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 11:26:10 by gdinet            #+#    #+#             */
/*   Updated: 2020/02/25 11:33:51 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "cub3d.h"

char	*verif_line(char *line)
{
	char	*str;
	int		len;
	int		i;

	i = -1;
	len = 0;
	while (line[++i])
	{
		if ((line[i] >= '0' && line[i] <= '2') || line[i] == 'N'
				|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
			len++;
		else if (line[i] != ' ')
			return (NULL);
	}
	i = 0;
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (*line)
	{
		if (*line != ' ')
			str[i++] = *line;
		line++;
	}
	str[i] = '\0';
	return (str);
}

int		add_to_list(char *line, t_list **map_list)
{
	char	*str;

	if (!(str = verif_line(line)))
		return (0);				//error msg
	ft_lstadd_back(map_list, ft_lstnew(str));
	return (1);
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

int		verif_map(t_map *map)
{
	int		x;
	int		y;

	y = -1;
	while (map->map[++y])
	{
		x = -1;
		while (map->map[y][++x])
		{
			if ((y == 0 || x == 0 || !map->map[y + 1] || !map->map[y][x + 1])
					&& map->map[y][x] != '1')
				return (0);			//error msg
			if (ft_isalpha(map->map[y][x]))
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
	return (1);
}

int		parse_map(t_map *map, char *line)
{
	static t_list	*map_list = NULL;

	if (*line)
		return (add_to_list(line, &map_list));
	else
	{
		if (!list_to_array(map_list, map))
			return (0);			//error msg
		ft_lstclear(&map_list, NULL);
		return (verif_map(map));
	}
}
