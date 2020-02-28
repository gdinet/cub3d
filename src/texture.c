/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 10:56:11 by gdinet            #+#    #+#             */
/*   Updated: 2020/02/28 12:39:41 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	get_color(float dist, float angle, float high, t_map *map)
{
	int		hit_x;
	float	step;

	hit_x = (int)floor(dist * sin(angle * M_PI / 180));
	step = map->north.height / high;
}
