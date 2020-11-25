/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 11:26:10 by gdinet            #+#    #+#             */
/*   Updated: 2020/11/25 15:28:55 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "cub3d.h"

void	add_to_list(char *line, t_list **map_list)
{
	char	*str;

	if (!is_map(line))
		error_msg("error10\n");					//msg
	if (!(str = ft_strdup(line)))
		error_msg("error11\n");				//error msg
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

void	add_sprite(t_map *map, int x, int y)
{
	t_sprite	*new;

	if (!(new = malloc(sizeof(t_sprite))))
		error_msg("malloc error\n");
	new->pos_x = x + 0.5;
	new->pos_y = y + 0.5;
	ft_lstadd_front(&(map->lst_sprite), ft_lstnew(new));
}

void	pos_item(t_map *map)
{
	int		x;
	int		y;

	y = -1;
	while (map->map[++y])
	{
		x = -1;
		while (map->map[y][++x])
		{
			if (map->map[y][x] == '2')
				add_sprite(map, x, y);
			if (ft_isalpha(map->map[y][x]))				//verif player non attribue
			{
				if (map->map[y][x] == 'N' || map->map[y][x] == 'S')
					map->angle = (map->map[y][x] == 'S') ? 90.1 : 270.1;
				if (map->map[y][x] == 'E' || map->map[y][x] == 'W')
					map->angle = (map->map[y][x] == 'E') ? 0.1 : 180.1;
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
			error_msg("error12\n");			//error msg
		ft_lstclear(&map_list, NULL);
		pos_item(map);
	}
}
