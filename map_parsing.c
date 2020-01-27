/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 11:26:10 by gdinet            #+#    #+#             */
/*   Updated: 2020/01/27 10:57:09 by gdinet           ###   ########.fr       */
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
	int		i;

	if (!(str = verif_line(line)))
		return (0);				//error msg
	ft_lstadd_back(map_list, ft_lstnew(str));
	return (1);
}

int		list_to_array(t_list *map_list, t_data *data)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = map_list;
	if (!(data->map = malloc(sizeof(char *) * (ft_lstsize(map_list) + 1))))
		return (0);
	while (tmp)
	{
		data->map[i] = tmp->content;
		i++;
		tmp = tmp->next;
	}
	data->map[i] = NULL;
	return (1);
}

int		verif_map(t_data *data)
{
	int		x;
	int		y;

	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if ((y == 0 || x == 0 || !data->map[y + 1] || !data->map[y][x + 1])
					&& data->map[y][x] != '1')
				return (0);			//error msg
			if (ft_isalpha(data->map[y][x]))
			{
				if (data->map[y][x] == 'N')
					data->angle = 0;
				if (data->map[y][x] == 'E')
					data->angle = 90;
				if (data->map[y][x] == 'S')
					data->angle = 180;
				if (data->map[y][x] == 'W')
					data->angle = 270;
				data->map[y][x] = '0';
				data->pos_x = x;
				data->pos_y = y;
			}
		}
	}
	return (1);
}

int		parse_map(t_data *data, char *line)
{
	static t_list	*map_list = NULL;

	if (*line)
		return (add_to_list(line, &map_list));
	else
	{
		if (!list_to_array(map_list, data))
			return (0);			//error msg
		ft_lstclear(&map_list, NULL);
		return (verif_map(data));
	}
}
