/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 14:32:22 by gdinet            #+#    #+#             */
/*   Updated: 2020/02/26 11:16:42 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>

t_mlx		init_mlx(t_map *map)
{
	t_mlx	mlx;

	mlx.mlx_ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx_ptr, map->res_x, map->res_y, "Cub3d");
	mlx.img_ptr = mlx_new_image(mlx.mlx_ptr, map->res_x, map->res_y);
	mlx.img = (int *)mlx_get_data_addr(mlx.img_ptr, &mlx.bpp, &mlx.size, &mlx.endian);
	return (mlx);
}

void	mlx_end(t_mlx *mlx)
{
	free(mlx->img);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win);
}
