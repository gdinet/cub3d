/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 14:32:22 by gdinet            #+#    #+#             */
/*   Updated: 2020/11/30 15:18:44 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>

t_mlx		init_mlx(void)
{
	t_mlx	mlx;

	mlx.mlx_ptr = mlx_init();
	return (mlx);
}

void		init_win(t_param *param)
{
	param->mlx->win = mlx_new_window(param->mlx->mlx_ptr, param->map->res_x,
	param->map->res_y, "Cub3d");
	param->mlx->img_ptr = mlx_new_image(param->mlx->mlx_ptr, param->map->res_x,
	param->map->res_y);
	param->mlx->img = (int *)mlx_get_data_addr(param->mlx->img_ptr,
	&param->mlx->bpp, &param->mlx->size, &param->mlx->endian);
}

t_map		init_map(void)
{
	t_map	map;

	map.res_x = 0;
	map.res_y = 0;
	map.north.img = NULL;
	map.south.img = NULL;
	map.east.img = NULL;
	map.west.img = NULL;
	map.sprite.img = NULL;
	map.floor = -1;
	map.ceil = -1;
	map.lst_sprite = NULL;
	map.pos_x = -1.0;
	map.pos_y = -1.0;
	map.angle = -1.0;
	return (map);
}
