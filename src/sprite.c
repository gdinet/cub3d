/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:32:30 by gdinet            #+#    #+#             */
/*   Updated: 2020/11/09 17:02:42 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"
#include <math.h>

void	sprite_dist(float x, float y, t_list *lst_sprite)
{
	t_list		*tmp;
	t_sprite	*sprite;

	tmp = lst_sprite;
	while (tmp)
	{
		sprite = tmp->content;
		sprite->dist = pow(x - sprite->pos_x, 2) + pow(y - sprite->pos_y, 2);
		tmp = tmp->next;
	}
}

int		cmp_sprite(t_sprite *s1, t_sprite *s2)
{
	if (s1->dist >= s2->dist)
		return (0);
	return (1);
}

void	sort_sprite(float x, float y, t_list *lst_sprite)
{
	t_list		*tmp;
	t_sprite	*sprite;

	sprite_dist(x, y, lst_sprite);
	tmp = lst_sprite;
	while (tmp && tmp->next)
	{
		if (cmp_sprite(tmp->content, tmp->next->content))
		{
			sprite = tmp->content;
			tmp->content = tmp->next->content;
			tmp->next->content = sprite;
			tmp = lst_sprite;
		}
		else
			tmp = tmp->next;
	}
}
