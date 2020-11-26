/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 11:26:10 by gdinet            #+#    #+#             */
/*   Updated: 2020/11/26 15:42:55 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "cub3d.h"

void	add_to_list(char *line, t_list **map_list, t_param *param)
{
	char	*str;

	if (!is_map(line))
		error_msg("Map : incorrect character", param);
	if (!(str = ft_strdup(line)))
		error_msg("Malloc error", param);
	ft_lstadd_back(map_list, ft_lstnew(str));
}

void	list_to_array(t_list *map_list, t_param *param)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = map_list;
	if (!(param->map->map = malloc(sizeof(char *) * (ft_lstsize(map_list) + 1))))
		error_msg("Malloc error", param);
	while (tmp)
	{
		param->map->map[i] = tmp->content;
		i++;
		tmp = tmp->next;
	}
	param->map->map[i] = NULL;
}

void	add_sprite(t_param *param, int x, int y)
{
	t_sprite	*new;

	if (!(new = malloc(sizeof(t_sprite))))
		error_msg("Malloc error", param);
	new->pos_x = x + 0.5;
	new->pos_y = y + 0.5;
	ft_lstadd_front(&(param->map->lst_sprite), ft_lstnew(new));
}

void	pos_item(t_param *param)
{
	int		x;
	int		y;

	y = -1;
	while (param->map->map[++y])
	{
		x = -1;
		while (param->map->map[y][++x])
		{
			if (param->map->map[y][x] == '2')
				add_sprite(param, x, y);
			if (ft_isalpha(param->map->map[y][x]))
			{
				if (param->map->pos_x != -1.0)
					error_msg("Beginning position already set", param);
				if (param->map->map[y][x] == 'N' || param->map->map[y][x] == 'S')
					param->map->angle = (param->map->map[y][x] == 'S') ? 90.1 : 270.1;
				if (param->map->map[y][x] == 'E' || param->map->map[y][x] == 'W')
					param->map->angle = (param->map->map[y][x] == 'E') ? 0.1 : 180.1;
				param->map->map[y][x] = '0';
				param->map->pos_x = x + 0.5;
				param->map->pos_y = y + 0.5;
			}
		}
	}
}

void	parse_map(t_param *param, char *line)
{
	static t_list	*map_list = NULL;

	if (line)
		add_to_list(line, &map_list, param);
	else
	{
		list_to_array(map_list, param);
		ft_lstclear(&map_list, NULL);
		pos_item(param);
	}
}
